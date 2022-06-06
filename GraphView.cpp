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

    edge = nullptr;
    cursor = nullptr;
    startingDFSNode = nullptr;
    endingDFSNode = nullptr;
    phantomEdge = nullptr;
    animationGroupDFS = nullptr;
    clickedDFS = false;

    connect(nodeButton, &QRadioButton::clicked, this, &GraphView::setNodeCursor);
    connect(nodeButton, &QRadioButton::clicked, this, [this]{if(edge) {edge->startingNode = nullptr;}}); //If Node button was clicked mid choosing 2nd edge reset the starting node
    connect(edgeButton, &QRadioButton::clicked, this, &GraphView::deleteCursor);
    connect(DFSButton, &QPushButton::pressed, this, [this]{clickedDFS = true;});
    connect(&graph, &Graph::endOfDFS, this, &GraphView::colorNodes);


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

        Node *node = new Node(QPointF(pos.x(), pos.y()));
        node->setPos(QPointF(node->center.x()-node->rect().width()/2, node->center.y()-node->rect().height()/2));
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
                if(edge && edge->startingNode) {
                    deletePhantomEdge();
                    edge->endingNode = clickedNode;

                    edge->setLine(QLineF(edge->startingNode->center, edge->endingNode->center));
                    graph.addEdge(edge);
                    scene->addItem(edge);

                    edge->startingNode = nullptr;
                    edge->endingNode = nullptr;
                }
                else {
                    edge = new Edge();
                    edge->startingNode = clickedNode;
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
        updateCursor(pos);

    }
    else if (edgeButton->isChecked()) {
        if(edge && edge->startingNode) {
            deletePhantomEdge();
            createPhantomEdge(edge->startingNode->center, event->pos());
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

void GraphView::createPhantomEdge(const QPointF &startingPosition, const QPointF &endingPosition)
{
    phantomEdge = new QGraphicsLineItem();
    phantomEdge->setLine(QLineF(startingPosition, endingPosition));
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

void GraphView::updateCursor(const QPointF &pos)
{
    QGraphicsEllipseItem *nodeCursor = dynamic_cast<QGraphicsEllipseItem*>(cursor);
    if(nodeCursor) {
        nodeCursor->setPos(pos.x()-nodeCursor->rect().width()/2, pos.y()-nodeCursor->rect().height()/2);

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
