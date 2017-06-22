#ifndef SHAPEITEMCHANGEGEOMETRYCOMMAND_H
#define SHAPEITEMCHANGEGEOMETRYCOMMAND_H

#include "itemundocommand.h"
#include "json.hpp"
using json = nlohmann::json;

class QGraphicsItem;

class ShapeItemChangeGeometryCommand : public ItemUndoCommand
{
public:
    ShapeItemChangeGeometryCommand(QGraphicsItem *item);

    void undo();
    void redo();
private:
    QGraphicsItem *shapeItem;
    json originGeometry;
    json newGeometry;
};

#endif // SHAPEITEMCHANGEGEOMETRYCOMMAND_H
