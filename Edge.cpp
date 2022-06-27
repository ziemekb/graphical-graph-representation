#include "Edge.h"

Edge::Edge()
{
    startingNode = nullptr;
    endingNode = nullptr;
    weight = 0;
}

Edge::Edge(Node *startingNode, Node *endingNode, int weight)
{
    this->setLine(QLineF(startingNode->getCenter(), endingNode->getCenter()));
    this->startingNode = startingNode;
    this->endingNode = endingNode;
    this->weight = weight;
}

Edge::~Edge()
{
    startingNode = nullptr;
    endingNode = nullptr;
}


int Edge::getWeight()
{
    return this->weight;
}

void Edge::setWeight(int weight)
{
    this->weight = weight;
}
