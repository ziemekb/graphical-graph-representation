#ifndef WEIGHTEDUNDIRECTEDGRAPH_H
#define WEIGHTEDUNDIRECTEDGRAPH_H

#include "AbstractGraph.h"

class WeightedUndirectedGraph : public AbstractGraph {
public:
    void addEdge(Node *startingNode, Node *endingNode) override;
    void addEdge(Edge *edge) override;
    void removeEdge(Edge *edge) override;

    void setWeight(Edge *edge, int weight);
};

#endif // WEIGHTEDUNDIRECTEDGRAPH_H
