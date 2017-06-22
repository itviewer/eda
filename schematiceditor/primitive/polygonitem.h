#ifndef PolygonItem_H
#define PolygonItem_H

#include <QGraphicsPolygonItem>

#include "abstractshapeitem.h"

class PolygonItem : public QGraphicsPolygonItem,public AbstractShapeItem
{
public:
    PolygonItem(SchematicScene *scene, QGraphicsItem *parent = nullptr);
    PolygonItem(SchematicScene *scene,const json &j, QGraphicsItem *parent = nullptr);

    ~PolygonItem();

    enum {
        Type = Item::PolygonItemType
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

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
private:
    void drawControlPoints();
    inline void initial();

};

#endif // PolygonItem_H
