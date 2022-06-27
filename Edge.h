#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsLineItem>
#include "Node.h"

class Edge : public QGraphicsLineItem {

public:
    Edge();
    Edge(Node *startingNode, Node *endingNode, int weight = 1);
    ~Edge();

    Node *startingNode;
    Node *endingNode;
    int getWeight();
    void setWeight(int weight);

private:
    int weight;
};

#endif // EDGE_H
