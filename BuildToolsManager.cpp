#include "BuildToolsManager.h"


BuildToolsManager::BuildToolsManager()
{
    nodeCursor = new NodeCursor;
    destructionCursor = new DestructionCursor;
    phantomEdge = new PhantomEdge;
}

void BuildToolsManager::update(buttonID checkedID, const QPointF &pos, Node *node)
{
    if(checkedID == nodeButtonID) {
        nodeCursor->updateCursor(pos);
    }
    else if(checkedID == destroyButtonId) {
        destructionCursor->updateCursor(pos);
    }
    else if(checkedID == edgeButtonID) {
        if(node) {
            // ... to be continued
        }
    }

}

NodeCursor *BuildToolsManager::getNodeCursor() const
{
    return nodeCursor;
}

DestructionCursor *BuildToolsManager::getDestructionCursor() const
{
    return destructionCursor;
}

PhantomEdge *BuildToolsManager::getPhantomEdge() const
{
    return phantomEdge;
}

