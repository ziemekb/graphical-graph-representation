#ifndef ABSTRACTCURSOR_H
#define ABSTRACTCURSOR_H

#include <QGraphicsItem>

class AbstractCursor {

public:
    virtual void updateCursor(const QPointF &pos) = 0;
    //virtual ~AbstractCursor();

protected:
    QGraphicsItem *cursor;
};

#endif // ABSTRACTCURSOR_H