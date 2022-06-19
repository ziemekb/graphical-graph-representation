#ifndef GRAPHREPRESENTATION_H
#define GRAPHREPRESENTATION_H

#include <QWidget>
#include <QGraphicsScene>
#include <QToolBar>
#include <QToolButton>
#include <QComboBox>
#include <QPushButton>
#include "MainWindow.h"
#include "NodeCursor.h"
#include "BuildToolsManager.h"


class GraphRepresentation : public QGraphicsScene {
public:
    GraphRepresentation(const graphType type);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
    QToolBar *graphToolBar;

    QButtonGroup *graphBuildButtonGroup;
    void generateToolBar(const graphType type);

    QComboBox *algorithmComboBox;
    QPushButton *startAlgorithmButton;

    BuildToolsManager buildToolsManager;
    //AbstractGraph graph; in constructor - graph = graphFactory->createGraph(graphType);
    //GraphFactory *graphFactory;

public slots:
    void placeGraphicsItem(QGraphicsItem *item);
};


#endif // GRAPHREPRESENTATION_H
