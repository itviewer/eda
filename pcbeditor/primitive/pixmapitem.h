#ifndef PixmapItem_H
#define PixmapItem_H


#include <QGraphicsPixmapItem>
#include "global.h"

class PCBScene;

class PixmapItem : public QGraphicsPixmapItem
{
public:
    PixmapItem(PCBScene *scene,const QPixmap &pixmap, QGraphicsItem *parent = nullptr);
    ~PixmapItem();

    PCBScene *pcbScene;

    void selected();
    void unselected();

    enum {
        Type = Item::PixmapItemType
    };

    int type() const;

//    void createCommandAdd();
//    void createCommandRemove();
//    void createCommandMove();

protected:
//    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void keyPressEvent(QKeyEvent *event);

};

#endif // PixmapItem_H
