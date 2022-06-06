#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsLineItem>
#include "Node.h"

class Edge : public QGraphicsLineItem {

public:
    Node *startingNode;
    Node *endingNode;
    int weight;

    Edge();
    Edge(Node *startingNode, Node *endingNode, int weight = 0);
    ~Edge();
};

#endif // EDGE_H
