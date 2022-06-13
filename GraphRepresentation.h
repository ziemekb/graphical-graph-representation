#ifndef GRAPHREPRESENTATION_H
#define GRAPHREPRESENTATION_H

#include <QWidget>
#include <QGraphicsScene>
#include <QToolBar>
#include <QToolButton>
#include <QComboBox>
#include <QPushButton>
#include "MainWindow.h"

enum buttonID {
    nodeButtonID,
    edgeButtonID
};

class GraphRepresentation : public QWidget {
public:
    GraphRepresentation(const graphType type);
    QGraphicsScene *getScene() const;

private:
    QGraphicsScene *scene;

    QToolBar *graphToolBar;

    QButtonGroup *graphBuildButtonGroup;
    void generateToolBar(const graphType type);

    QComboBox *algorithmComboBox;
    QPushButton *startAlgorithmButton;
    //AbstractGraph graph; in constructor - graph = graphFactory->createGraph(graphType);
    //GraphFactory *graphFactory;
};


#endif // GRAPHREPRESENTATION_H
