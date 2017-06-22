#ifndef ROUNDEDRECTITEM_H
#define ROUNDEDRECTITEM_H

#include <QGraphicsItem>

#include "abstractshapeitem.h"

class RoundedRectItem : public QGraphicsRoundedRectItem,public AbstractShapeItem
{
public:
    RoundedRectItem(SchematicScene *scene,QGraphicsItem *parent = nullptr);
    RoundedRectItem(SchematicScene *scene,const json &j, QGraphicsItem *parent = nullptr);
    ~RoundedRectItem();

    enum {
        Type = Item::RoundedRectItemType
    };

    void selected();
    void unselected();

    int type() const;

    void createCommandAdd();
    void createCommandRemove();
    void createCommandMove();
    void createCommandChangeGeometry();

    void setGeometry(const json &geometry) Q_DECL_OVERRIDE;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

//    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

    void keyPressEvent(QKeyEvent* keyEvent);

private:
    void drawControlPoints();
    inline void initial();
};

#endif // ROUNDEDRECTITEM_H
