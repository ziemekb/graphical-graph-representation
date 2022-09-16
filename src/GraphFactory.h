#ifndef GRAPHFACTORY_H
#define GRAPHFACTORY_H

#include "AbstractGraph.h"
#include "MainWindow.h"

class GraphFactory : public QObject {
Q_OBJECT
public:
    AbstractGraph *getGraph(const graphType type);

signals:
    graphType graphTypeSignal(graphType type);

};

#endif // GRAPHFACTORY_H
