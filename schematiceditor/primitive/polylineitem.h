#ifndef POLYLINEITEM_H
#define POLYLINEITEM_H

#include <QGraphicsItem>

#include "abstractshapeitem.h"

class PolylineItem : public QGraphicsPolylineItem,public AbstractShapeItem
{
public:
    PolylineItem(SchematicScene *scene, QGraphicsItem *parent = nullptr);
    PolylineItem(SchematicScene *scene,const json &j, QGraphicsItem *parent = nullptr);

    ~PolylineItem();

    enum {
        Type = Item::PolylineItemType
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

#endif // POLYLINEITEM_H
