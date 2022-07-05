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
    static graphType type;
    int weight;
    QGraphicsTextItem *weightText;
    void setWeightFromText();

    QLineF shortenQLineF(QPointF startingPoint, QPointF endingPoint);

public slots:
    void receiveGraphType(graphType type);

signals:
    void weightChangeSignal(Edge *edge, int weight);
};

#endif // EDGE_H
