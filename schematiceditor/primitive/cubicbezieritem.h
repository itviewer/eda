#ifndef CUBICBEZIERITEM_H
#define CUBICBEZIERITEM_H

#include <QGraphicsPathItem>

#include "abstractshapeitem.h"

class CubicBezierItem : public QGraphicsPathItem,public AbstractShapeItem
{
public:
    CubicBezierItem(SchematicScene *scene,QGraphicsItem *parent = nullptr);
    CubicBezierItem(SchematicScene *scene,const json &j, QGraphicsItem *parent = nullptr);

    ~CubicBezierItem();

    enum {
        Type = Item::CubicBezierItemType
    };

    void selected();
    void unselected();

    int type() const;

    QPolygonF getPolygon() const;
    void setPolygon(const QPolygonF &polygon);

    void createCommandAdd();
    void createCommandRemove();
    void createCommandMove();
    void createCommandChangeGeometry();

    void setGeometry(const json &geometry) Q_DECL_OVERRIDE;
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

private:
    QPolygonF metaPolygon;
    void drawControlPoints();
    inline void initial();
};

#endif // CUBICBEZIERITEM_H
