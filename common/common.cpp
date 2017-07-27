#include "common.h"
#include <QCoreApplication>
#include <QTime>
#include <QElapsedTimer>
#include <QFile>
#include <QCryptographicHash>
#include <QDebug>

/**
 * ***********************************************************************
 *
 * 非持久化全局变量
 *
 * ***********************************************************************
 */
QString settingDir = "";

/**
 * ***********************************************************************
 *
 *  标识符重载
 *
 * ***********************************************************************
 */
QDebug operator<<(QDebug out, const json &js)
{
    out.noquote() << QString::fromStdString(js.dump(4));
    return out;
}

/**
 * ***********************************************************************
 *
 * 全局函数
 *
 * ***********************************************************************
 */
void sleep(int milliseconds, int step)
{
    QElapsedTimer timer;
    timer.start();
    while(timer.elapsed() < milliseconds) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, step);
    }
}

Qt::ToolBarArea dockAreaToToolBarArea(Qt::DockWidgetArea area)
{
    switch(area) {
        case Qt::LeftDockWidgetArea: return Qt::LeftToolBarArea;
        case Qt::RightDockWidgetArea: return Qt::RightToolBarArea;
        case Qt::TopDockWidgetArea: return Qt::TopToolBarArea;
        case Qt::BottomDockWidgetArea: return Qt::BottomToolBarArea;
        default:
            return Qt::ToolBarArea(0);
    }
}

Qt::Orientation areaToOrientation(Qt::DockWidgetArea area)
{
    switch(area) {
        case Qt::LeftDockWidgetArea:
        case Qt::RightDockWidgetArea:
            return Qt::Vertical;
        case Qt::TopDockWidgetArea:
        case Qt::BottomDockWidgetArea:
            return Qt::Horizontal;
        default:
            return Qt::Horizontal;
    }
}

bool loadJsonDocument(const QString &filename, json &j, const JsonFormat &format)
{
    QFile loadFile(filename);
    //json文件不能含注释，key必须是字符串
    if(loadFile.open(QIODevice::ReadOnly)) {
        //直接返回而不是先赋值给临时变量 对大文件可避免一次复制
        //TODO 是否能取消返回值自动将key排序
        if(format == JsonFormat::Json) {
            j.merge(json::parse(loadFile.readAll().toStdString()));
            return true;
        } else {
            j.merge(json::parse(loadFile.readAll().toStdString()));
            return true;
        }
    }
    // 不需要显示关闭文件 QFile父类析构时自动关闭
    return false;
}

bool saveJsonDocument(const QString &filename, const json &j, const JsonFormat &format)
{
    QFile saveFile(filename);

    if(saveFile.open(QIODevice::WriteOnly)) {

        saveFile.write(format == JsonFormat::Json
                       ? QByteArray::fromStdString(j.dump(4))
                       : QByteArray::fromStdString(j.dump()));
        return true;
    }

    return false;
}

QString md5(const QString &str, const QString &salt, bool middle)
{
    return middle ? QString(QCryptographicHash::hash((str + salt).toUtf8(), QCryptographicHash::Md5).toHex()).mid(8, 16) :
                    QString(QCryptographicHash::hash((str + salt).toUtf8(), QCryptographicHash::Md5).toHex());
}

int random(int min, int max)
{
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    return qrand() % (max - min) + min;
}

const QPointF gridPoint(QPointF point, const int gridSize)
{
    point.setX(round(point.x()/gridSize)*gridSize);
    point.setY(round(point.y()/gridSize)*gridSize);
    return point;
}
