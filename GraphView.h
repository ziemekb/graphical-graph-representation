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
#include "Edge.h"

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
    QGroupBox *horizontalGroupBox;
    QRadioButton *nodeButton;
    QRadioButton *edgeButton;
    QPushButton *DFSButton;
    void radioButtonReset();

    Edge *edge;
    QGraphicsLineItem *phantomEdge;
    void createPhantomEdge(const QPointF &startingPosition, const QPointF &endingPosition);
    void deletePhantomEdge();

    QGraphicsItem *cursor;
    void updateCursor(const QPointF &pos);
    void setCursor(QGraphicsItem *item);

    Graph graph;
    bool clickedDFS; // I don't like this solution
    Node *startingDFSNode; // Prob should be implemented in some other way
    Node *endingDFSNode;   // maybe as Edge *DFSEdge when starting and ending node is implemented in Edge but without
                           // adding it to Graph graph? actually a bad idea I think
                           // Maybe as algorithmStartingNode and algorithEndingNode and reused with other algorithms
    QSequentialAnimationGroup *animationGroupDFS;

public slots:
    void colorNodes(QQueue<Node*> nodesToColor);
    void setNodeCursor();
    void deleteCursor();
};

#endif // GRAPHVIEW_H
