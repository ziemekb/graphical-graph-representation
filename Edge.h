#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include "Node.h"
#include "MainWindow.h"

class Edge : public QObject, public QGraphicsLineItem {
Q_OBJECT
public:
    static Edge *createEdge(Node *startingNode, Node *endingNode, const graphType type);
    Edge();
    Edge(Node *startingNode, Node *endingNode, bool weighted = false, bool directed = false);
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
