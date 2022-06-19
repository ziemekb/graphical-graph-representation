#include <QGraphicsProxyWidget>
#include "DestructionCursor.h"

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
            return;
        }
    }

    this->show();
}
