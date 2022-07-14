#include "UnweightedDirectedGraph.h"

void UnweightedDirectedGraph::addEdge(Edge *edge)
{
    adjList[edge->startingNode].insert(edge->endingNode, edge);
}

void UnweightedDirectedGraph::removeEdge(Edge *edge)
{
    adjList[edge->startingNode].remove(edge->endingNode);
}
