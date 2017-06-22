#ifndef LINEITEM_H
#define LINEITEM_H

#include <QGraphicsLineItem>

#include "abstractshapeitem.h"

class LineItem : public QGraphicsLineItem,public AbstractShapeItem
{
public:
    LineItem(PartScene *scene,QGraphicsItem *parent = nullptr);
    LineItem(PartScene *scene,const json &j, QGraphicsItem *parent = nullptr);

    ~LineItem();

    enum {
        Type = Item::LineItemType
    };

    void selected();
    void unselected();

    int type() const;

//    void createCommandAdd();
//    void createCommandRemove();
//    void createCommandMove();
//    void createCommandChangeGeometry();
//    void createCommandRotation();
//    void createCommandGroupRotation();

    void setGeometry(const json &geometry) Q_DECL_OVERRIDE;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

//    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

    void keyPressEvent(QKeyEvent* keyEvent);

private:
    void drawControlPoints();
    inline void initial();
};

#endif // LINEITEM_H
