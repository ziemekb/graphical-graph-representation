#include <QGraphicsProxyWidget>
#include "DestructionCursor.h"


DestructionCursor::DestructionCursor()
{
    cursor = new QGraphicsPixmapItem; //check what happens when passing this as a parent later in GraphRepresentation

    QGraphicsPixmapItem *tempCursor = static_cast<QGraphicsPixmapItem*>(cursor);

    QPixmap destructionPixmap(":/assets/hammer_icon.png");

    destructionPixmap = destructionPixmap.scaled(QSize(40, 40), Qt::KeepAspectRatio);

    this->pixmapHeight = destructionPixmap.height();
    this->pixmapWidth = destructionPixmap.width();

    tempCursor->setPixmap(destructionPixmap);

    tempCursor->hide();
}

void DestructionCursor::updateCursor(const QPointF &pos)
{
    QGraphicsPixmapItem *tempCursor = static_cast<QGraphicsPixmapItem*>(cursor);

    tempCursor->setPos(pos.x()-this->pixmapWidth/2, pos.y()-this->pixmapHeight/2);

    QList<QGraphicsItem*> collidingItems = tempCursor->collidingItems();


    for(auto const &e : collidingItems) {
        if(typeid(*e) == typeid(QGraphicsProxyWidget)) {
            tempCursor->hide();
            return;
        }
    }
    tempCursor->show();
}
