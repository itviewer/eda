#ifndef WIRE_H
#define WIRE_H

#include <QList>

class WireSegmentItem;
class JunctionItem;
class PortItem;
class SchematicScene;

class Wire
{
public:
    Wire(SchematicScene *scene);

    SchematicScene *schScene;
    // 不能用QVector
    QList<WireSegmentItem *> wireItems;

    WireSegmentItem *firstItem() const;
    WireSegmentItem *lastItem() const;

    void createCommandAdd();

    void setAttachedNet(const QString &net);
    const QString attachedNet();

    int count() const;
    bool isEmpty() const;
    void append(WireSegmentItem *wireSegmentItem);
    void prepend(WireSegmentItem *wireSegmentItem);
    void preInsert(WireSegmentItem *wireSegmentItem,WireSegmentItem *newItem);
    void nextInsert(WireSegmentItem *wireSegmentItem,WireSegmentItem *newItem);

    void removeFirst();
    void removeLast();
    bool removeOne(WireSegmentItem *wireSegmentItem);

    JunctionItem *attachedStartJunction() const;
    JunctionItem *attachedEndJunction() const;
    PortItem *attachedStartPort() const;
    PortItem *attachedEndPort() const;

    Wire * removeSplit(WireSegmentItem *wireSegmentItem);
    Wire * junctionSplit(WireSegmentItem *wireSegmentItem,JunctionItem *junction);
    void merge(Wire *wire);
private:
    QString netName;

};

#endif // WIRE_H
