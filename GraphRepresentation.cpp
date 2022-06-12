#include <GraphView.h>
#include "GraphRepresentation.h"

GraphRepresentation::GraphRepresentation(graphType graphType) {
    scene = new QGraphicsScene;
    scene->setSceneRect(0, 0, Constansts::SCREEN_WIDTH, Constansts::SCREEN_HEIGHT);
}

QGraphicsScene *GraphRepresentation::getScene() const
{
    return scene;
}
