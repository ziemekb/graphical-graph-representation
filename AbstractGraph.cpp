#include "AbstractGraph.h"

void AbstractGraph::DFS(Node* startingNode, Node* soughtNode)
{
    visited[startingNode] = true;

    nodesToColor.enqueue(startingNode);

    if(startingNode == soughtNode) {
        emit nodesToColorSignal(nodesToColor);
        nodesToColor.clear();
        return;
    }

    QHash<Node*, int>::const_iterator i;

    for(i  = adjList[startingNode].constBegin(); i != adjList[startingNode].constEnd(); ++i) {
        if(!visited[i.key()]) {
            this->DFS(i.key(), soughtNode);
        }
    }
}

QList<Node *> AbstractGraph::getKeys()
{
    return adjList.keys();
}
