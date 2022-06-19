#ifndef BUILDTOOLSMANAGER_H
#define BUILDTOOLSMANAGER_H

#include "NodeCursor.h"
#include "DestructionCursor.h"
#include "Node.h"

enum buttonID {
    nodeButtonID,
    edgeButtonID,
    destroyButtonId
};

class BuildToolsManager {
public:
    BuildToolsManager();
    void update(buttonID checkedID, const QPointF &pos, Node *node = nullptr);
    NodeCursor* getNodeCursor() const;
    DestructionCursor* getDestructionCursor() const;
    //PhantomEdge* getPhantomEdge() const;

private:
    NodeCursor *nodeCursor;
    DestructionCursor *destructionCursor;
    //PhantomEdge* phantomEdge;
};


#endif // BUILDTOOLSMANAGER_H
