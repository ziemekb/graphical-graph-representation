#ifndef GRAPHREPRESENTATION_H
#define GRAPHREPRESENTATION_H

#include <QWidget>
#include <QGraphicsScene>
#include <QToolBar>
#include <QToolButton>
#include <QComboBox>
#include <QPushButton>
#include <QParallelAnimationGroup>
#include <QStackedWidget>
#include "MainWindow.h"
#include "NodeCursor.h"
#include "BuildToolsManager.h"
#include "AbstractGraph.h"
#include "GraphFactory.h"


class GraphRepresentation : public QGraphicsScene {
Q_OBJECT
public:
    static bool animationState;
    //static graphType type;

    GraphRepresentation(const graphType type);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    QToolBar *graphToolBar;

    QButtonGroup *graphBuildButtonGroup;
    void resetRadioButtons();
    void generateToolBar(const graphType type);

    QComboBox *algorithmComboBox;
    //const QStringList algorithmTypes = {"DFS", "BFS", "Dijkstra"};
    QPushButton *startAlgorithmButton;

    BuildToolsManager buildToolsManager;
    void checkForNode(const QPointF &pos);

    AbstractGraph *graph;
    GraphFactory graphFactory;

    QParallelAnimationGroup *initialAnimation;
    void setInitialAnimation(QQueue<Node*> nodesToColor);

    QSequentialAnimationGroup *nodeColoringAnimation;

    void setAlgorithmAnimationPanel();
    QStackedWidget *userInstructions;
    void advanceUserInstructions();
    //QGraphicsSimpleTextItem *userInstructions;
    QPushButton *quitAnimationButton;
    void returnToBuildMode();

public slots:
    void placeGraphicsItem(QGraphicsItem *item);
    void removeGraphicsItem(QGraphicsItem *item);
    void drawAlgorithmAnimationPanel();
    void showNodeColoringAnimation(QQueue<Node*> nodesToColor);
    void setEdgeWeight(Edge *edge, int weight);

signals:
    void clickedNodeWithPos(const QPointF &pos, Node *node);
    void clickedNode(Node *node);
    void clickedDestroy();
    void algorithmTypeSignal(algorithmType aType);
};


#endif // GRAPHREPRESENTATION_H
