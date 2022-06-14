#ifndef NODECURSOR_H
#define NODECURSOR_H

#include "AbstractCursor.h"

class NodeCursor : public AbstractCursor {
public:
    NodeCursor();
    void updateCursor(const QPointF &pos) override;
};


#endif // NODECURSOR_H
