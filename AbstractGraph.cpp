#include "AbstractGraph.h"

AbstractGraph::AbstractGraph()
{
    algorithmStartingNode = nullptr;
    algorithmEndingNode = nullptr;
}

void AbstractGraph::DFS(Node* startingNode, Node* soughtNode)
{
    visited[startingNode] = true;

    nodesToColor.enqueue(startingNode);

    if(startingNode == soughtNode) {
        emit nodesToColorSignal(nodesToColor);
    }
    else {
        QHash<Node*, int>::const_iterator i;

        for(i  = adjList[startingNode].constBegin(); i != adjList[startingNode].constEnd(); ++i) {
            if(!visited[i.key()]) {
                this->DFS(i.key(), soughtNode);
            }
        }
    }
}

QList<Node*> AbstractGraph::getKeys()
{
    return adjList.keys();
}

void AbstractGraph::receiveNode(Node *node)
{
    qDebug() << "receive Node";
    if(!algorithmStartingNode) {
        algorithmStartingNode = node;
        return;
    }

    algorithmEndingNode = node;

    switch(aType) {
    case dfs:
        this->DFS(algorithmStartingNode, algorithmEndingNode);
        break;
    case bfs:
        //this->BFS(algorithmStartingNode, algorithmEndingNode);
        break;
    case dijkstra:
        //this->dijkstra(algorithmStartingNode, algorithmEndingNode);
        break;
    default:
        qDebug() << "unknown algorithm type";
        break;
    }

    algorithmStartingNode = nullptr;
    algorithmEndingNode = nullptr;
    resetVisited();
    nodesToColor.clear();
}

void AbstractGraph::getAlgorithmType(algorithmType aType)
{
    this->aType = aType;
}

void AbstractGraph::resetVisited()
{
    for(auto const &e : getKeys()) {
        visited[e] = false;
    }
}
