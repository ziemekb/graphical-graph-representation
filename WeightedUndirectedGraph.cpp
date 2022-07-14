#include "WeightedUndirectedGraph.h"

void WeightedUndirectedGraph::addEdge(Edge *edge) {

    adjList[edge->startingNode].insert(edge->endingNode, edge);
    adjList[edge->endingNode].insert(edge->startingNode, edge);
}

void WeightedUndirectedGraph::removeEdge(Edge *edge) {

    adjList[edge->startingNode].remove(edge->endingNode);
    adjList[edge->endingNode].remove(edge->startingNode);
}
