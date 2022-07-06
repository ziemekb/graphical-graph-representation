#include "UnweightedDirectedGraph.h"

void UnweightedDirectedGraph::addEdge(Node *startingNode, Node *endingNode)
{
    adjList[startingNode].insert(endingNode, 1);
}

void UnweightedDirectedGraph::addEdge(Edge *edge)
{
    adjList[edge->startingNode].insert(edge->endingNode, 1);
}

void UnweightedDirectedGraph::removeEdge(Edge *edge)
{
    adjList[edge->startingNode].remove(edge->endingNode);
}
