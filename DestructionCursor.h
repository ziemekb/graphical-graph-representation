#ifndef DESTRUCTIONCURSOR_H
#define DESTRUCTIONCURSOR_H

#include "AbstractCursor.h"

class DestructionCursor : public AbstractCursor {
public:
    DestructionCursor();
    void updateCursor(const QPointF &pos) override;
private:
    int pixmapHeight;
    int pixmapWidth;
};

#endif // DESTRUCTIONCURSOR_H
