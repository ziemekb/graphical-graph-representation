#include "UnweightedUndirectedGraph.h"

void UnweightedUndirectedGraph::addEdge(Node *startingNode, Node *endingNode)
{
    this->adjList[startingNode].insert(endingNode, 1);
    this->adjList[endingNode].insert(startingNode, 1);
}

void UnweightedUndirectedGraph::addEdge(Edge *edge) {

    adjList[edge->startingNode].insert(edge->endingNode, 1);
    adjList[edge->endingNode].insert(edge->startingNode, 1);
}

void UnweightedUndirectedGraph::removeEdge(Edge *edge)
{
    adjList[edge->startingNode].remove(edge->endingNode);
    adjList[edge->endingNode].remove(edge->startingNode);
}

