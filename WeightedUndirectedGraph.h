#ifndef WEIGHTEDUNDIRECTEDGRAPH_H
#define WEIGHTEDUNDIRECTEDGRAPH_H

#include "AbstractGraph.h"

class WeightedUndirectedGraph : public AbstractGraph {

public:
    void addEdge(Edge *edge) override;
    void removeEdge(Edge *edge) override;
};

#endif // WEIGHTEDUNDIRECTEDGRAPH_H
