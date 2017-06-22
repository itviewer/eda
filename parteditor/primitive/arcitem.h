#ifndef ArcItem_H
#define ArcItem_H

#include <QGraphicsPathItem>

#include "abstractshapeitem.h"

class ArcItem : public QGraphicsPathItem,public AbstractShapeItem
{
public:
    ArcItem(PartScene *scene,QGraphicsItem *parent = nullptr);
    ArcItem(PartScene *scene,const json &j, QGraphicsItem *parent = nullptr);

    ~ArcItem();

    enum {
        Type = Item::ArcItemType
    };

    void selected();
    void unselected();

    int type() const;

    QRectF getRect() const;
    void setRect(const QRectF &rect);

    qreal getStartAngle() const;
    void setStartAngle(qreal angle);

    qreal getSweepLength() const;
    void setSweepLength(qreal length);

//    void createCommandAdd();
//    void createCommandRemove();
//    void createCommandMove();
//    void createCommandChangeGeometry();

    void setGeometry(const json &geometry) Q_DECL_OVERRIDE;


protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

private:
    QRectF metaRect;
    qreal metaStartAngle;
    qreal metaSweepLength;

//    QPainterPath boundingItemPath;

    void drawControlPoints();
    inline void initial();
};

#endif // ArcItem_H
