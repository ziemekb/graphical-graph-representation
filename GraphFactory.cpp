#include "GraphFactory.h"
#include "UnweightedUndirectedGraph.h"

AbstractGraph *GraphFactory::getGraph(const graphType type)
{
    if(type == unweightedUndirected) {
        return new UnweightedUndirectedGraph;
    }
    else if(type == unweightedDirected) {
        //return new UnweightedDirectedGraph;
    }
    else if(type == weightedUndirected) {
        //return new WeightedUndirectedGraph;
    }
    else if(type == weightedDirected) {
        //return new WeightedDirectedGraph;
    }

    return new UnweightedUndirectedGraph;
}
