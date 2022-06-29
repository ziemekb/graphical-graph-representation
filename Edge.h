#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include "Node.h"
#include "MainWindow.h"

class Edge : public QObject, public QGraphicsLineItem {
Q_OBJECT
public:
    Edge();
    Edge(Node *startingNode, Node *endingNode);
    ~Edge();

    Node *startingNode;
    Node *endingNode;
    int getWeight();
    void setWeight(int weight);

private:
    int weight;
    QGraphicsTextItem *weightText;
    void setWeightFromText();
    static graphType type;

public slots:
    void receiveGraphType(graphType type);
};

#endif // EDGE_H
