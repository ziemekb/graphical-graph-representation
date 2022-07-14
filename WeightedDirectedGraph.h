#ifndef WEIGHTEDDIRECTEDGRAPH_H
#define WEIGHTEDDIRECTEDGRAPH_H

#include "AbstractGraph.h"

class WeightedDirectedGraph : public AbstractGraph {

public:
    void addEdge(Edge *edge) override;
    void removeEdge(Edge *edge) override;
};

#endif // WEIGHTEDDIRECTEDGRAPH_H
