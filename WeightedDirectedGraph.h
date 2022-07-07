#ifndef WEIGHTEDDIRECTEDGRAPH_H
#define WEIGHTEDDIRECTEDGRAPH_H

#include "AbstractGraph.h"

class WeightedDirectedGraph : public AbstractGraph {

public:
    void addEdge(Node *startingNode, Node *endingNode) override;
    void addEdge(Edge *edge) override;
    void removeEdge(Edge *edge) override;

    void setWeight(Edge *edge, int weight);
};

#endif // WEIGHTEDDIRECTEDGRAPH_H
