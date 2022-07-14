#include "WeightedDirectedGraph.h"

void WeightedDirectedGraph::addEdge(Edge *edge)
{
    adjList[edge->startingNode].insert(edge->endingNode, edge);
}

void WeightedDirectedGraph::removeEdge(Edge *edge)
{
    adjList[edge->startingNode].remove(edge->endingNode);
}
