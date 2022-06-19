#include <QPen>
#include <QToolBar>
#include <QGraphicsProxyWidget>
#include "NodeCursor.h"
#include "Node.h"
#include "Edge.h"


NodeCursor::NodeCursor()
{
    cursor = new QGraphicsEllipseItem; //check what happens when passing this as a parent later in GraphRepresentation

    QGraphicsEllipseItem *tempCursor = static_cast<QGraphicsEllipseItem*>(cursor);

    tempCursor->setRect(0, 0, Node::nodeWidth, Node::nodeHeight);
    tempCursor->setPen(QPen(Qt::green));
    tempCursor->hide();
}

void NodeCursor::updateCursor(const QPointF &pos)
{
    QGraphicsEllipseItem *tempCursor = static_cast<QGraphicsEllipseItem*>(cursor);

    tempCursor->setPos(pos.x()-Node::nodeWidth/2, pos.y()-Node::nodeHeight/2);

    QList<QGraphicsItem*> collidingItems = tempCursor->collidingItems();

    if(collidingItems.isEmpty()) {
       tempCursor->setPen(QPen(Qt::green));
       tempCursor->show();
    }
    else {
        for(auto const &e : collidingItems) {
            if(typeid(*e) == typeid(QGraphicsProxyWidget)) {
                tempCursor->hide();
                break;
            }
            else if(typeid(*e) == typeid(Node) || typeid(*e) == typeid(Edge)) {
                tempCursor->setPen(QPen(Qt::red));
                tempCursor->show();
            }
        }
    }
}
