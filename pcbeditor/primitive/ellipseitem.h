#ifndef EllipseItem_H
#define EllipseItem_H

#include <QGraphicsEllipseItem>

#include "abstractshapeitem.h"

class EllipseItem : public QGraphicsEllipseItem,public AbstractShapeItem
{
public:
    EllipseItem(PCBScene *scene,QGraphicsItem *parent = nullptr);
    EllipseItem(PCBScene *scene,const json &j, QGraphicsItem *parent = nullptr);

    ~EllipseItem();

    enum {
        Type = Item::EllipseItemType
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

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
private:
    void drawControlPoints();
    inline void initial();

};

#endif // EllipseItem_H
