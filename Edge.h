#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include "Node.h"

class Edge : public QObject, public QGraphicsLineItem {
Q_OBJECT
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
    QGraphicsTextItem *weightText;
    void setWeightFromText();
};

#endif // EDGE_H
