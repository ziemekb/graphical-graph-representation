#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsLineItem>
#include "Node.h"

class Edge : public QGraphicsLineItem {

public:
    Node *startingNode;
    Node *endingNode;
    int weight;

};

#endif // EDGE_H
