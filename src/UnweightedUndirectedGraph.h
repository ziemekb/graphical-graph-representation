#ifndef UNWEIGHTEDUNDIRECTEDGRAPH_H
#define UNWEIGHTEDUNDIRECTEDGRAPH_H

#include "AbstractGraph.h"

class UnweightedUndirectedGraph : public AbstractGraph {

public:
    void addEdge(Edge *edge) override;
    void removeEdge(Edge *edge) override;
};

#endif // UNWEIGHTEDUNDIRECTEDGRAPH_H
