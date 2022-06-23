#include "AbstractGraph.h"

AbstractGraph::AbstractGraph()
{
    algorithmStartingNode = nullptr;
    algorithmEndingNode = nullptr;
}

void AbstractGraph::runAlgorithm(algorithmType aType)
{
    /*
    switch(aType) {
        case dfs:
            this->DFS();
        break;
    }
    */
}

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

QList<Node*> AbstractGraph::getKeys()
{
    return adjList.keys();
}

void AbstractGraph::receiveNode(const QPointF &pos, Node *node)
{
    if(!algorithmStartingNode) {
        algorithmStartingNode = node;
        return;
    }

    algorithmEndingNode = node;

    qDebug() << "run DFS";
    this->DFS(algorithmStartingNode, algorithmEndingNode);

    algorithmStartingNode = nullptr;
    algorithmEndingNode = nullptr;
}
