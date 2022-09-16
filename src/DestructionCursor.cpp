#include <QGraphicsProxyWidget>
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include "DestructionCursor.h"
#include "Node.h"
#include "Edge.h"

DestructionCursor::DestructionCursor()
{
    QPixmap destructionPixmap(":/assets/hammer_icon2.png");

    //this->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    destructionPixmap = destructionPixmap.scaled(QSize(40, 40), Qt::KeepAspectRatio);

    this->pixmapHeight = destructionPixmap.height();
    this->pixmapWidth = destructionPixmap.width();

    this->setPixmap(destructionPixmap);

    this->hide();
}

void DestructionCursor::updateCursor(const QPointF &pos)
{
    this->setPos(pos.x()-this->pixmapWidth/2, pos.y()-this->pixmapHeight/2);

    QList<QGraphicsItem*> collidingItems = this->collidingItems();

    for(auto const &e : collidingItems) {
        if(typeid(*e) == typeid(QGraphicsProxyWidget)) {
            this->hide();
            setHoveredOnItemsPen(Qt::black);
            itemsToBeDestroyed.clear();
            return;
        }
    }

    this->show();
    findItemsToBeDestroyed();
}

void DestructionCursor::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    for(auto const &e : itemsToBeDestroyed) {

        if(typeid(*e) == typeid(Node)) {
            QList <QGraphicsItem*> collidingWithNode = e->collidingItems();

            for (auto const &f : collidingWithNode) {
                if(typeid(*f) == typeid(Edge)) {
                    emit graphicsItemToRemove(f);
                }
            }

            emit graphicsItemToRemove(e);
        }
        else if (typeid(*e) == typeid(Edge)) {
            emit graphicsItemToRemove(e);
        }
    }

    itemsToBeDestroyed.clear();

    QGraphicsPixmapItem::mousePressEvent(event);
}

void DestructionCursor::findItemsToBeDestroyed()
{
    setHoveredOnItemsPen(Qt::black);

    itemsToBeDestroyed = this->collidingItems();

    setHoveredOnItemsPen(Qt::red);
}

void DestructionCursor::setHoveredOnItemsPen(QColor color)
{
    for(auto const &e : itemsToBeDestroyed) {

        Node *node = dynamic_cast<Node*>(e);
        Edge *edge = dynamic_cast<Edge*>(e);

        if(node) {
            node->setPen(QPen(color));
        }
        else if(edge) {
            edge->setPen(QPen(color));
        }
    }
}
