#ifndef DESTRUCTIONCURSOR_H
#define DESTRUCTIONCURSOR_H

#include <QObject>
#include <QGraphicsPixmapItem>

class DestructionCursor : public QObject, public QGraphicsPixmapItem {
Q_OBJECT
public:
    DestructionCursor();
    void updateCursor(const QPointF &pos);
private:
    int pixmapHeight;
    int pixmapWidth;
    QList <QGraphicsItem*> itemsToBeDestroyed;
    void findItemsToBeDestroyed();
    void setHoveredOnItemsPen(QColor color);
};

#endif // DESTRUCTIONCURSOR_H
