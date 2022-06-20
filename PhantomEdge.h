#ifndef PHANTOMEDGE_H
#define PHANTOMEDGE_H

#include <QGraphicsLineItem>
#include "Node.h"

class PhantomEdge : public QObject,  public QGraphicsLineItem {
Q_OBJECT
public:
    PhantomEdge();
    void update(const QPointF &pos);
private:
    Node *startingNode;

public slots:
    void receiveNode(const QPointF &pos, Node *node);
};

#endif // PHANTOMEDGE_H
