#include <QPen>
#include "PhantomEdge.h"

PhantomEdge::PhantomEdge()
{
    startingNode = nullptr;
}

void PhantomEdge::update(const QPointF &pos, Node *node)
{
    startingNode = node;
    this->setLine(QLineF(startingNode->center, pos));
    this->setPen(QPen(Qt::gray));
    //scene->addItem(phantomEdge);
}

void PhantomEdge::update(const QPointF &pos)
{
    if(startingNode) {
        this->setLine(QLineF(startingNode->center, pos));
    }
}
