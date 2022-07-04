#include "WeightedUndirectedGraph.h"

void WeightedUndirectedGraph::addEdge(Node *startingNode, Node *endingNode)
{
    this->adjList[startingNode].insert(endingNode, 1);
    this->adjList[endingNode].insert(startingNode, 1);
}

void WeightedUndirectedGraph::addEdge(Edge *edge) {

    adjList[edge->startingNode].insert(edge->endingNode, 1);
    adjList[edge->endingNode].insert(edge->startingNode, 1);
}

void WeightedUndirectedGraph::removeEdge(Edge *edge)
{
    adjList[edge->startingNode].remove(edge->endingNode);
    adjList[edge->endingNode].remove(edge->startingNode);
}

void WeightedUndirectedGraph::setWeight(Edge *edge, int weight)
{
    qDebug() << "change weight to" << weight;
    this->adjList[edge->startingNode][edge->endingNode] = weight;
    this->adjList[edge->endingNode][edge->startingNode] = weight;
}

