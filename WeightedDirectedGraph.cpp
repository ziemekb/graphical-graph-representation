#include "WeightedDirectedGraph.h"

void WeightedDirectedGraph::addEdge(Node *startingNode, Node *endingNode)
{
    adjList[startingNode].insert(endingNode, 1);
}

void WeightedDirectedGraph::addEdge(Edge *edge)
{
    adjList[edge->startingNode].insert(edge->endingNode, 1);
}

void WeightedDirectedGraph::removeEdge(Edge *edge)
{
    adjList[edge->startingNode].remove(edge->endingNode);
}

void WeightedDirectedGraph::setWeight(Edge *edge, int weight)
{
    adjList[edge->startingNode][edge->endingNode] = weight;
}
