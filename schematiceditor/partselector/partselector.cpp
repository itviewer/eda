#include "partselector.h"
#include "parttable.h"
#include "partpreviewer.h"
#include "statepartitem.h"

#include "db.h"
#include "schematiceditor.h"
#include "statemachine.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>

PartSelector::PartSelector(const QString &title, QWidget *parent, Qt::WindowFlags flags)
    : QDockWidget(title, parent, flags)
{
    setFixedWidth(260);
    setAllowedAreas(Qt::RightDockWidgetArea);
    setFeatures(DockWidgetClosable | DockWidgetFloatable | DockWidgetMovable);

    // QDockWidget 有默认的QDockWidgetLayout 所以内容只能在一个新的widget中布局
    QWidget *contentWidget = new QWidget;

    // 整体垂直布局
    QVBoxLayout *vLayout = new QVBoxLayout(contentWidget);
    vLayout->setContentsMargins(0,5,5,1);

    QComboBox *libSelector = new QComboBox(contentWidget);
    libSelector->addItems(QStringList({"所有库", "test"}));
    QLineEdit *searchBar = new QLineEdit(contentWidget);

    partTable = new PartTable(this, contentWidget);
    connect(partTable, &PartTable::pressed, this, &PartSelector::onPartPressed);
    connect(partTable, &PartTable::doubleClicked, this, &PartSelector::onPartDoubleClicked);

    //元件预览和package、供应商按钮整体水平布局
    QHBoxLayout *hLayout = new QHBoxLayout;
    // package和供应商按钮垂直布局
    QVBoxLayout *vvLayout = new QVBoxLayout;

    partPreviewer = new PartPreviewer(contentWidget);

    QGroupBox *package = new QGroupBox("Packaging", contentWidget);
    // package布局
    QVBoxLayout *packageLayout = new QVBoxLayout(package);
    packageLayout->setMargin(4);

    // 三行元件信息及各自水平布局
    QLabel *labelParts = new QLabel("Parts per Pkg:", package);
    labelPartsValue = new QLabel("1", package);
    QHBoxLayout *h1LayoutOfPackage = new QHBoxLayout;
    h1LayoutOfPackage->addWidget(labelParts);
    h1LayoutOfPackage->addWidget(labelPartsValue);

    QLabel *labelPart = new QLabel("Part:", package);
    partSelector = new QComboBox(package);
    partSelector->setDisabled(true);
    QHBoxLayout *h2LayoutOfPackage = new QHBoxLayout;
    h2LayoutOfPackage->addWidget(labelPart);
    h2LayoutOfPackage->addWidget(partSelector);

    QLabel *labelType = new QLabel("Type:", package);
    labelTypeValue = new QLabel(package);
    QHBoxLayout *h3LayoutOfPackage = new QHBoxLayout;
    h3LayoutOfPackage->addWidget(labelType);
    h3LayoutOfPackage->addWidget(labelTypeValue);

    QPushButton *buttonProvider = new QPushButton("查找供应商", contentWidget);

    packageLayout->addLayout(h1LayoutOfPackage);
    packageLayout->addLayout(h2LayoutOfPackage);
    packageLayout->addLayout(h3LayoutOfPackage);

    vvLayout->addWidget(package);
    vvLayout->addWidget(buttonProvider);

    hLayout->addWidget(partPreviewer);
    hLayout->addLayout(vvLayout);

    vLayout->addWidget(libSelector);
    vLayout->addWidget(searchBar);
    vLayout->addWidget(partTable);
    vLayout->addLayout(hLayout);

    setWidget(contentWidget);

    statePartItem = static_cast<StatePartItem *>(fsm->state(FSM::PartItemState));
}

void PartSelector::onPartLibraryChanged()
{
    partTable->updateModel();
}

void PartSelector::onPartPressed(const QModelIndex &index)
{
    if (previewIndex != index) {

        const QVariantHash result = partLib->get("select md5,json from part_parts where partid=?"
                                                 , {index.column() ? index.sibling(index.row(), 0).data() : index.data()});

        previewPart = json::parse(result.value("json").toString().toStdString());

        bool enabled = partSelector->isEnabled();
        if (enabled) {
            partSelector->disconnect();
            partSelector->clear();
        }

        partNumbers = previewPart["partNumbers"];
        labelPartsValue->setText(QString::number(partNumbers));

        if (partNumbers == 1 && enabled) {
            partSelector->setEnabled(false);
        } else if (partNumbers > 1) {
            partSelector->setEnabled(true);

            if (int(previewPart["partNumbering"])) {
                for (int i = 1; i <= partNumbers; i++) {
                    partSelector->addItem(QString::number(i));
                }
            } else {
                // 确保parts小于26
                for (int i = 0; i < partNumbers; i++) {
                    partSelector->addItem(alphabet.at(i));
                }
            }

            connect(partSelector, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, [ = ](int partIndex) {
                partPreviewer->setPart(partIndex);
                if (currentPartMD5 != previewPartMD5) {
                    currentPart = previewPart;
                    currentPartMD5 = previewPartMD5;
                    createPart(true, partIndex);
                } else {
                    // 大于等于当前最大值则继续否则新建
                    if (partIndex > statePartItem->currentPartIndex() && partIndex < partNumbers) {
                        createPart(false, partIndex);
                    } else {
                        createPart(true, partIndex);
                    }
                }
            });
        }

        partPreviewer->setPart(0);

        previewPartMD5 = result.value("md5").toString();
    }
    previewIndex = index;
}

void PartSelector::onPartDoubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index)
    // 是否在同一元件上双击 否则新建元件
    if (currentPartMD5 != previewPartMD5) {
        currentPart = previewPart;
        currentPartMD5 = previewPartMD5;
        createPart(true);
    } else {
        // 同一元件双击判断当前是否为绘图状态
        // 主动终止或页面切换都会重置绘图状态
        if (!statePartItem->isDrawing) {
            // 多门元件如果不是开始部分且没有超过最大部分则继续
            if (partNumbers > 1) {
                int partIndex = statePartItem->currentPartIndex() + 1;
                if (partIndex && partIndex < partNumbers) {
                    createPart(false, partIndex);
                } else {
                    createPart(true);
                }
            } else {
                createPart(true);
            }
        }
    }
}

void PartSelector::createPart(bool newPart, int partIndex)
{
    // 无论什么情况 必须先检测并设置场景状态
    if (fsm->currentState() != FSM::PartItemState) {
        schEditor->setSceneState(FSM::PartItemState);
    }
    statePartItem->createPartItem(newPart, partIndex);
}
