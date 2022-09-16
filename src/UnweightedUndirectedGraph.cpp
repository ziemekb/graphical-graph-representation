#include "UnweightedUndirectedGraph.h"

void UnweightedUndirectedGraph::addEdge(Edge *edge) {

    adjList[edge->startingNode].insert(edge->endingNode, edge);
    adjList[edge->endingNode].insert(edge->startingNode, edge);
}

void UnweightedUndirectedGraph::removeEdge(Edge *edge)
{
    adjList[edge->startingNode].remove(edge->endingNode);
    adjList[edge->endingNode].remove(edge->startingNode);
}

