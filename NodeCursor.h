#ifndef NODECURSOR_H
#define NODECURSOR_H

#include "AbstractCursor.h"
#include "Node.h"

class NodeCursor : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT
public:
    NodeCursor();
    void updateCursor(const QPointF &pos);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    bool canPlace;

signals:
    void nodeToBePlaced(Node* node);
};


#endif // NODECURSOR_H
