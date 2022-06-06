#include <QPointF>
#include <QDebug>
#include <QList>
#include <QGraphicsItem>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QThread>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QButtonGroup>
#include "GraphView.h"
#include "Graph.h"
#include "Node.h"
#include "Edge.h"


GraphView::GraphView()
{
    setRenderHints(QPainter::Antialiasing);

    scene = new QGraphicsScene(this);
    this->setScene(scene);

    setMouseTracking(true);

    createHorizontalGroupBox();
    scene->addWidget(horizontalGroupBox);

    connect(nodeButton, &QRadioButton::clicked, this, &GraphView::setNodeCursor);
    connect(nodeButton, &QRadioButton::clicked, this, [this]{edgeStartingNode = nullptr;}); //If Node button was clicked mid choosing 2nd edge reset the starting node
    connect(edgeButton, &QRadioButton::clicked, this, &GraphView::deleteCursor);
    connect(DFSButton, &QPushButton::pressed, this, [this]{clickedDFS = true;});
    //connect(&graph, &Graph::checkedNode, this, &GraphView::getCheckedNode);
    connect(&graph, &Graph::endOfDFS, this, &GraphView::colorNodes);

    cursor = nullptr;
    edgeStartingNode = nullptr;
    edgeEndingNode = nullptr;
    startingDFSNode = nullptr;
    endingDFSNode = nullptr;
    phantomEdge = nullptr;
    animationGroupDFS = nullptr;
    clickedDFS = false;


    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    scene->setSceneRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}


void GraphView::mousePressEvent(QMouseEvent *event)
{
    QPointF pos = event->pos();

    if(clickedDFS) {

        radioButtonReset();

        QList itemsAt = items(event->pos());

        for(auto const &e : itemsAt) {
            Node *clickedNode = dynamic_cast<Node*>(e);
            if(clickedNode) {
                if(startingDFSNode) {

                    endingDFSNode = clickedNode;

                    graph.DFS(startingDFSNode, endingDFSNode);

                    startingDFSNode = nullptr;
                    endingDFSNode = nullptr;
                    clickedDFS = false;
                }
                else {
                    startingDFSNode = clickedNode;
                }
                break;
            }
        }
    }
    else if(nodeButton->isChecked()) {

        Node *node = new Node(QPointF(pos.rx(), pos.ry()));
        node->setPos(QPointF(node->center.rx()-node->rect().width()/2, node->center.ry()-node->rect().height()/2));
        scene->addItem(node);

        if(node->doesCollide()) {
            scene->removeItem(node);
            delete node;
        }
        else {
            graph.addNode();
        }
    }
    else if(edgeButton->isChecked()) {

        QList itemsAt = items(event->pos());

        for(auto const &e : itemsAt) {

            Node *clickedNode = dynamic_cast<Node*>(e);
            if(clickedNode) {
                if(edgeStartingNode) {
                    deletePhantomEdge();
                    edgeEndingNode = clickedNode;

                    Edge *edge = new Edge(); // I could add Edge *edge to Graph.h and startingNode and endingNode to Edge code
                                             // then reimplement addEdge(Node*, Node*) to addEdge(const Edge*) in Graph
                    edge->setLine(QLineF(edgeStartingNode->center, edgeEndingNode->center));
                    graph.addEdge(edgeStartingNode, edgeEndingNode);
                    scene->addItem(edge);

                    edgeStartingNode = nullptr;
                    edgeEndingNode = nullptr;

                }
                else {
                    edgeStartingNode = clickedNode;
                }
                break;
            }
        }
    }

    QGraphicsView::mousePressEvent(event);
}

void GraphView::mouseMoveEvent(QMouseEvent *event)
{
    QPointF pos = event->pos();

    if(nodeButton->isChecked()) {

        QGraphicsEllipseItem *nodeCursor = dynamic_cast<QGraphicsEllipseItem*>(cursor); //this is utter shit
        // Maybe QGraphicsEllipseItem* nodeCursorCollision(QGraphicsItem *cursor, const QPointF &pos) should be implemented?
        if(nodeCursor) {
            nodeCursor->setPos(QPointF(pos.rx()-nodeCursor->rect().width()/2, pos.ry()-nodeCursor->rect().height()/2));

            QList<QGraphicsItem*> collidingItems = scene->collidingItems(nodeCursor);

            if(collidingItems.isEmpty()) {
               nodeCursor->setPen(QPen(Qt::green));
               nodeCursor->show();
            }
            else {
                for(auto const &e : collidingItems) {
                    if(typeid(*e) == typeid(Node) || typeid(*e) == typeid(Edge)) {
                        nodeCursor->setPen(QPen(Qt::red));
                        nodeCursor->show();
                    }
                    else {
                        nodeCursor->hide();
                        break;
                    }
                }
            }
        }
    }
    else if (edgeButton->isChecked()) {
        if(edgeStartingNode) {
            deletePhantomEdge();
            createPhantomEdge(edgeStartingNode->center, event->pos());
        }
    }
}

void GraphView::createHorizontalGroupBox()
{
    nodeButton = new QRadioButton("Nodes");
    edgeButton = new QRadioButton("Edges");
    DFSButton = new QPushButton("DFS");


    horizontalGroupBox = new QGroupBox();
    QHBoxLayout *layout = new QHBoxLayout;

    layout->addWidget(nodeButton);
    layout->addWidget(edgeButton);
    layout->addWidget(DFSButton);

    horizontalGroupBox->setLayout(layout);
}

void GraphView::radioButtonReset()
{
    nodeButton->setAutoExclusive(false);
    edgeButton->setAutoExclusive(false);
    nodeButton->setChecked(false);
    edgeButton->setChecked(false);
    nodeButton->setAutoExclusive(true);
    edgeButton->setAutoExclusive(true);
}

void GraphView::createPhantomEdge(QPointF pos1, QPointF pos2)
{
    phantomEdge = new QGraphicsLineItem();
    phantomEdge->setLine(QLineF(pos1, pos2));
    phantomEdge->setPen(QPen(Qt::gray));
    scene->addItem(phantomEdge);
}

void GraphView::deletePhantomEdge()
{
    if(phantomEdge) {
        scene->removeItem(phantomEdge);
        phantomEdge = nullptr;
    }
}

/*
void GraphView::getCheckedNode(Node *checkedNode)
{
    nodesToColor.enqueue(checkedNode);
}
*/

void GraphView::colorNodes(QQueue<Node*> nodesToColor)
{
    animationGroupDFS = new QSequentialAnimationGroup;

    for(auto const &e : nodesToColor) {
        QPropertyAnimation *nodeAnim = new QPropertyAnimation(e, "color");
        nodeAnim->setDuration(1000);
        nodeAnim->setStartValue(QColor(Qt::white));
        if(startingDFSNode == e) {
            nodeAnim->setEndValue(QColor(Qt::yellow));
        }
        else if (endingDFSNode == e) {
            nodeAnim->setEndValue(QColor(Qt::red));
        }
        else {
            nodeAnim->setEndValue(QColor(Qt::lightGray));
        }

        animationGroupDFS->addAnimation(nodeAnim);
    }
    animationGroupDFS->start(); //(QAbstractAnimation::DeleteWhenStopped);
    nodesToColor.clear();
}

void GraphView::setCursor(QGraphicsItem *item)
{
    if(cursor) {
       scene->removeItem(cursor);
       cursor = nullptr;
    }

    cursor = item;
    scene->addItem(cursor);
    cursor->hide();
}

void GraphView::setNodeCursor()
{
    QGraphicsEllipseItem *cur = new QGraphicsEllipseItem();
    cur->setRect(0, 0, Node::nodeWidth, Node::nodeHeight);
    cur->setPen(QPen(Qt::red));
    this->setCursor(cur);
}

void GraphView::deleteCursor()
{
    if(cursor) {
       scene->removeItem(cursor);
       cursor = nullptr;
    }
}

