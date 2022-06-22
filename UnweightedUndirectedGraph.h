#ifndef UNWEIGHTEDUNDIRECTEDGRAPH_H
#define UNWEIGHTEDUNDIRECTEDGRAPH_H

#include "AbstractGraph.h"

class UnweightedUndirectedGraph : public AbstractGraph {

    void addEdge(Node *startingNode, Node *endingNode) override;
    void addEdge(Edge *edge) override;
    void removeEdge(Edge *edge) override;
};

#endif // UNWEIGHTEDUNDIRECTEDGRAPH_H
