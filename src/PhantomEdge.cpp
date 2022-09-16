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
        Edge *edge = new Edge(startingNode, node);
        emit edgeToBePlaced(edge);
        startingNode = nullptr;
        this->hide();
        return;
    }
    startingNode = node;
    this->setLine(QLineF(startingNode->getCenter(), pos));
    this->setPen(QPen(Qt::gray));
    this->show();
}

void PhantomEdge::receiveWeightChange(Edge *edge, int weight)
{
    emit weightChangeSignal(edge, weight);
}

void PhantomEdge::update(const QPointF &pos)
{
    if(startingNode) {
        this->setLine(QLineF(startingNode->getCenter(), pos));
        this->show();
    }
}
