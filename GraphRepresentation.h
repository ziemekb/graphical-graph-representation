#ifndef GRAPHREPRESENTATION_H
#define GRAPHREPRESENTATION_H

#include <QWidget>
#include <QGraphicsScene>
#include <QToolBar>
#include <QToolButton>
#include <QComboBox>
#include <QPushButton>
#include <QParallelAnimationGroup>
#include "MainWindow.h"
#include "NodeCursor.h"
#include "BuildToolsManager.h"
#include "AbstractGraph.h"
#include "GraphFactory.h"


class GraphRepresentation : public QGraphicsScene {
Q_OBJECT
public:
    GraphRepresentation(const graphType type);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    QToolBar *graphToolBar;

    QButtonGroup *graphBuildButtonGroup;
    void generateToolBar(const graphType type);

    QComboBox *algorithmComboBox;
    QPushButton *startAlgorithmButton;

    BuildToolsManager buildToolsManager;
    void checkForPhantomEdgeNode(const QPointF &pos);

    AbstractGraph *graph; //in constructor - graph = graphFactory->createGraph(graphType);
    GraphFactory graphFactory;

    QParallelAnimationGroup *initialAnimation;
    void setInitialAnimation(Node *node);
    void nodeColoringAnimation();

    QGraphicsSimpleTextItem *userInstructions;

public slots:
    void placeGraphicsItem(QGraphicsItem *item);
    void removeGraphicsItem(QGraphicsItem *item);
    void drawAlgorithmShowPanel();

signals:
    void clickedNode(const QPointF &pos, Node *node);
    void clickedDestroy();
};


#endif // GRAPHREPRESENTATION_H
