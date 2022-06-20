#include <QGraphicsProxyWidget>
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include "DestructionCursor.h"
#include "Node.h"
#include "Edge.h"

DestructionCursor::DestructionCursor()
{
    QPixmap destructionPixmap(":/assets/hammer_icon.png");

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
        if(node) {
            node->setPen(QPen(color));
        }

        Edge *edge = dynamic_cast<Edge*>(e);
        if(edge) {
            edge->setPen(QPen(color));
        }
    }
}
