#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QPushButton>
#include <QObject>
#include <QRadioButton>
#include <QGroupBox>
#include <QButtonGroup>
#include <QQueue>
#include <QAbstractAnimation>
#include "Node.h"
#include "Graph.h"
#include "Edge.h""

enum dataType {
    nodeType,
    edgeType
};

class GraphView : public QGraphicsView {

public:
    static constexpr int SCREEN_WIDTH = 800;
    static constexpr int SCREEN_HEIGHT = 600;

    GraphView();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    QGraphicsScene *scene;

    void createHorizontalGroupBox();
    QGroupBox *horizontalGroupBox; // Should this even be here?
    QRadioButton *nodeButton;
    QRadioButton *edgeButton;
    QPushButton *DFSButton;
    void radioButtonReset(); // Should add QButtonGroup coz this function is shit

    Edge *edge;
    //Node *edgeStartingNode; // Should be in Edge class
    //Node *edgeEndingNode;   // this too
    QGraphicsLineItem *phantomEdge;
    void createPhantomEdge(QPointF pos1, QPointF pos2);
    void deletePhantomEdge();

    QGraphicsItem *cursor;
    void setCursor(QGraphicsItem *item);

    Graph graph;
    //QQueue<Node*> nodesToColor; // Should be in Graph class
    bool clickedDFS; // I don't like this solution
    Node *startingDFSNode; // Prob should be implemented in some other way
    Node *endingDFSNode;   // maybe as Edge *DFSEdge when starting and ending node is implemented in Edge but without
                           // adding it to Graph graph? actually a bad idea I think
                           // Maybe as algorithmStartingNode and algorithEndingNode and reused with other algorithms
    QSequentialAnimationGroup *animationGroupDFS;

public slots:
    //void getCheckedNode(Node *checkedNode); //should be deleted and functionality moved to Graph class
    void colorNodes(QQueue<Node*> nodesToColor);
    void setNodeCursor();
    void deleteCursor();
};

#endif // GRAPHVIEW_H
