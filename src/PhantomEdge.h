#ifndef PHANTOMEDGE_H
#define PHANTOMEDGE_H

#include <QGraphicsLineItem>
#include "Node.h"
#include "Edge.h"

class PhantomEdge : public QObject,  public QGraphicsLineItem {
Q_OBJECT
public:
    PhantomEdge();
    void update(const QPointF &pos);
private:
    Node *startingNode;

public slots:
    void receiveNode(const QPointF &pos, Node *node);
    void receiveWeightChange(Edge *edge, int weight);

signals:
    void edgeToBePlaced(Edge *edge);
    void weightChangeSignal(Edge *edge, int weight);
};

#endif // PHANTOMEDGE_H
