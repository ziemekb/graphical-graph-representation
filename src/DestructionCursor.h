#ifndef DESTRUCTIONCURSOR_H
#define DESTRUCTIONCURSOR_H

#include <QObject>
#include <QGraphicsPixmapItem>

class DestructionCursor : public QObject, public QGraphicsPixmapItem {
Q_OBJECT
public:
    DestructionCursor();
    void updateCursor(const QPointF &pos);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    int pixmapHeight;
    int pixmapWidth;
    QList <QGraphicsItem*> itemsToBeDestroyed;
    void findItemsToBeDestroyed();
    void setHoveredOnItemsPen(QColor color);
signals:
    void graphicsItemToRemove(QGraphicsItem *item);
};

#endif // DESTRUCTIONCURSOR_H
