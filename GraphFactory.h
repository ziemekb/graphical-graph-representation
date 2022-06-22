#ifndef GRAPHFACTORY_H
#define GRAPHFACTORY_H

#include "AbstractGraph.h"
#include "MainWindow.h"

class GraphFactory {
public:
    AbstractGraph *getGraph(const graphType type);

};

#endif // GRAPHFACTORY_H
