#include <QPen>
#include <QToolBar>
#include <QGraphicsProxyWidget>
#include <QGraphicsSceneMouseEvent>
#include "NodeCursor.h"
#include "Edge.h"


NodeCursor::NodeCursor()
{
    this->setRect(0, 0, Node::nodeWidth, Node::nodeHeight);
    this->setPen(QPen(Qt::green));
    this->hide();
    this->canPlace = false;
}

void NodeCursor::updateCursor(const QPointF &pos)
{
    this->setPos(pos.x()-Node::nodeWidth/2, pos.y()-Node::nodeHeight/2);

    QList<QGraphicsItem*> collidingItems = this->collidingItems();

    if(collidingItems.isEmpty()) {
       this->setPen(QPen(Qt::green));
       this->show();
       this->canPlace = true;
    }
    else {
        for(auto const &e : collidingItems) {
            if(typeid(*e) == typeid(QGraphicsProxyWidget)) {
                this->hide();
                this->canPlace = false;
                break;
            }
            else if(typeid(*e) == typeid(Node) || typeid(*e) == typeid(Edge)) {
                this->setPen(QPen(Qt::red));
                this->show();
                this->canPlace = false;
            }
        }
    }
}

void NodeCursor::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pos = event->scenePos();

    if(canPlace) {
        Node *node = new Node(pos);
        node->setPos(QPointF(node->getCenter().x()-node->rect().width()/2, node->getCenter().y()-node->rect().height()/2));
        canPlace = false;
        this->setPen(QPen(Qt::red));
        emit nodeToBePlaced(node);
    }

    QGraphicsEllipseItem::mousePressEvent(event);
}
