#ifndef PHANTOMEDGE_H
#define PHANTOMEDGE_H

#include <QGraphicsLineItem>
#include "Node.h"

class PhantomEdge : public QGraphicsLineItem {
public:
    PhantomEdge();
    void update(const QPointF &pos, Node *node);
    void update(const QPointF &pos);
    //void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    Node *startingNode;
};

#endif // PHANTOMEDGE_H
