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
};

#endif // DESTRUCTIONCURSOR_H
