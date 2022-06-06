#include "Edge.h"

Edge::Edge()
{
    startingNode = nullptr;
    endingNode = nullptr;
    weight = 0;
}

Edge::Edge(Node *startingNode, Node *endingNode, int weight)
{
    this->startingNode = startingNode;
    this->endingNode = endingNode;
    this->weight = weight;
}

Edge::~Edge()
{
    delete startingNode;
    delete endingNode;
}


