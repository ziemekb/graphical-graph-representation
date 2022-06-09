#include "Graph.h"
#include "GraphView.h"


void Graph::addEdge(Edge *edge) {

    adjList[edge->startingNode].insert(edge->endingNode, 1);
    adjList[edge->endingNode].insert(edge->startingNode, 1);
}

void Graph::DFS(Node* startingNode, Node* soughtNode)
{
    visited[startingNode] = true;

    nodesToColor.enqueue(startingNode);

    if(startingNode == soughtNode) {
        qDebug() << "Found the node";
        emit endOfDFS(nodesToColor);
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
