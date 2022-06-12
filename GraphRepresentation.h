#ifndef GRAPHREPRESENTATION_H
#define GRAPHREPRESENTATION_H

#include <QWidget>
#include <QGraphicsScene>
#include "MainWindow.h"

class GraphRepresentation : public QWidget {
public:
    GraphRepresentation(graphType graphType);
    QGraphicsScene *getScene() const;

private:
    QGraphicsScene *scene;
    //AbstractGraph graph; in constructor - graph = graphFactory.createGraph(graphType); -> graphType needed in constructor
    //GraphFactory *graphFactory;
};


#endif // GRAPHREPRESENTATION_H
