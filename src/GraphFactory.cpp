#include "GraphFactory.h"
#include "UnweightedUndirectedGraph.h"
#include "WeightedUndirectedGraph.h"
#include "UnweightedDirectedGraph.h"
#include "WeightedDirectedGraph.h"

AbstractGraph *GraphFactory::getGraph(const graphType type)
{
    Edge edge;
    connect(this, &GraphFactory::graphTypeSignal, &edge, &Edge::receiveGraphType);
    emit graphTypeSignal(type);

    if(type == unweightedUndirected) {
        return new UnweightedUndirectedGraph;
    }
    else if(type == unweightedDirected) {
        return new UnweightedDirectedGraph;
    }
    else if(type == weightedUndirected) {
        return new WeightedUndirectedGraph;
    }
    else if(type == weightedDirected) {
        return new WeightedDirectedGraph;
    }

    return new UnweightedUndirectedGraph;
}
