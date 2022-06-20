#include <QPen>
#include <QGraphicsSceneMouseEvent>
#include "PhantomEdge.h"

PhantomEdge::PhantomEdge()
{
    startingNode = nullptr;
}

void PhantomEdge::receiveNode(const QPointF &pos, Node *node)
{
    if(startingNode) {
        // placeEdge(startingNode, node);
        return;
    }
    startingNode = node;
    this->setLine(QLineF(startingNode->center, pos));
    this->setPen(QPen(Qt::gray));
    this->show();
}

void PhantomEdge::update(const QPointF &pos)
{
    if(startingNode) {
        this->setLine(QLineF(startingNode->center, pos));
        this->show();
    }
}
