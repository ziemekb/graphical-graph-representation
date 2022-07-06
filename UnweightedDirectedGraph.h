#ifndef UNWEIGHTEDDIRECTEDGRAPH_H
#define UNWEIGHTEDDIRECTEDGRAPH_H

#include "AbstractGraph.h"

class UnweightedDirectedGraph : public AbstractGraph {

public:
    void addEdge(Node *startingNode, Node *endingNode) override;
    void addEdge(Edge *edge) override;
    void removeEdge(Edge *edge) override;
};

#endif // UNWEIGHTEDDIRECTEDGRAPH_H
