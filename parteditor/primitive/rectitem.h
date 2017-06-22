#ifndef RECTITEM_H
#define RECTITEM_H

#include <QGraphicsRectItem>

#include "abstractshapeitem.h"


class RectItem : public QGraphicsRectItem,public AbstractShapeItem
{
public:
    RectItem(PartScene *scene,QGraphicsItem *parent = nullptr);
    RectItem(PartScene *scene,const json &j, QGraphicsItem *parent = nullptr);
    ~RectItem();

    enum {
        Type = Item::RectItemType
    };

    void selected();
    void unselected();

    int type() const;

//    void createCommandAdd();
//    void createCommandRemove();
//    void createCommandMove();
//    void createCommandChangeGeometry();

    void setGeometry(const json &geometry) Q_DECL_OVERRIDE;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

    void keyPressEvent(QKeyEvent* keyEvent);

private:
    void drawControlPoints();
    inline void initial();
};

#endif // RECTITEM_H
