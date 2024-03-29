#include <QVBoxLayout>
#include <QDebug>
#include <QButtonGroup>
#include <QGraphicsSceneMouseEvent>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QLabel>
#include <QGraphicsSimpleTextItem>
#include "GraphRepresentation.h"
#include "PhantomEdge.h"
#include "WeightedUndirectedGraph.h"
#include "WeightedDirectedGraph.h"

bool GraphRepresentation::animationState = false;

GraphRepresentation::GraphRepresentation(const graphType type) {
    this->setSceneRect(0, 0, Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT);

    this->addItem(buildToolsManager.getDestructionCursor());
    this->addItem(buildToolsManager.getNodeCursor());
    this->addItem(buildToolsManager.getPhantomEdge());

    graph = graphFactory.getGraph(type);

    nodeColoringAnimation = new QSequentialAnimationGroup;
    initialAnimation = new QParallelAnimationGroup;

    generateToolBar(type);
    setAlgorithmAnimationPanel();

    connect(buildToolsManager.getNodeCursor(), &NodeCursor::nodeToBePlaced, this, &GraphRepresentation::placeGraphicsItem);
    connect(this, &GraphRepresentation::clickedNodeWithPos, buildToolsManager.getPhantomEdge(), &PhantomEdge::receiveNode);
    connect(buildToolsManager.getPhantomEdge(), &PhantomEdge::edgeToBePlaced, this, &GraphRepresentation::placeGraphicsItem);
    connect(buildToolsManager.getDestructionCursor(), &DestructionCursor::graphicsItemToRemove, this, &GraphRepresentation::removeGraphicsItem);
    connect(this, &GraphRepresentation::clickedNode, graph, &AbstractGraph::receiveNode);
    connect(startAlgorithmButton, &QPushButton::clicked, this, &GraphRepresentation::drawAlgorithmAnimationPanel);
    connect(startAlgorithmButton, &QPushButton::clicked, this, [this] {
        emit algorithmTypeSignal(static_cast<algorithmType>(algorithmComboBox->currentData().toInt()));
    });
    connect(this, &GraphRepresentation::algorithmTypeSignal, graph, &AbstractGraph::getAlgorithmType);
    connect(graph, &AbstractGraph::graphColoringSignal, this, &GraphRepresentation::showNodeColoringAnimation);
    connect(quitAnimationButton, &QPushButton::clicked, this, &GraphRepresentation::returnToBuildMode);
    connect(initialAnimation, &QParallelAnimationGroup::finished, this, [this]{this->initialAnimation->clear();});
    connect(nodeColoringAnimation, &QSequentialAnimationGroup::finished, this, [this]{this->nodeColoringAnimation->clear();});
}

void GraphRepresentation::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    buildToolsManager.update(static_cast<buttonID>(graphBuildButtonGroup->checkedId()), event->scenePos());

    QGraphicsScene::mouseMoveEvent(event);
}

void GraphRepresentation::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    checkForNode(event->scenePos());

    if(graphBuildButtonGroup->checkedId() == destroyButtonId) {
        emit clickedDestroy();
    }

    QGraphicsScene::mousePressEvent(event);
}

void GraphRepresentation::resetRadioButtons()
{
    if(graphBuildButtonGroup->checkedButton()) {

        graphBuildButtonGroup->setExclusive(false);

        graphBuildButtonGroup->checkedButton()->setChecked(false);

        graphBuildButtonGroup->setExclusive(true);
    }
}

void GraphRepresentation::generateToolBar(const graphType type)
{
    graphToolBar = new QToolBar();

    //Adding buttons associated with graph creation
    QToolButton *nodeButton = new QToolButton(graphToolBar);
    QToolButton *edgeButton = new QToolButton(graphToolBar);
    QToolButton *destroyButton = new QToolButton(graphToolBar);

    nodeButton->setIcon(QIcon(":/assets/circle_icon.png"));
    edgeButton->setIcon(QIcon(":/assets/edge_icon.png"));
    destroyButton->setIcon(QIcon(":/assets/hammer_icon2.png"));

    nodeButton->setCheckable(true);
    edgeButton->setCheckable(true);
    destroyButton->setCheckable(true);

    //Organizing buttons in a button group
    graphBuildButtonGroup = new QButtonGroup;

    graphBuildButtonGroup->addButton(nodeButton, nodeButtonID);
    graphBuildButtonGroup->addButton(edgeButton, edgeButtonID);
    graphBuildButtonGroup->addButton(destroyButton, destroyButtonId);

    //Adding buttons to QToolBar

    graphToolBar->addWidget(nodeButton);
    graphToolBar->addWidget(edgeButton);
    graphToolBar->addWidget(destroyButton);

    graphBuildButtonGroup->setExclusive(true);

    graphToolBar->addSeparator();

    //Adding QComboBox with available algorithms
    algorithmComboBox = new AlgorithmComboBox;

    graphToolBar->addWidget(algorithmComboBox);

    graphToolBar->addSeparator();

    //Adding start algorithm button
    startAlgorithmButton = new QPushButton("Start algorithm");

    graphToolBar->addWidget(startAlgorithmButton);

    this->addWidget(graphToolBar);
}

void GraphRepresentation::checkForNode(const QPointF &pos)
{
    if(graphBuildButtonGroup->checkedId() != edgeButtonID && !animationState) {
        return;
    }

    QList itemsAt = items(pos);

    for(auto const &e : itemsAt) {
        Node *node = dynamic_cast<Node*>(e);
        if(node) {
            if(animationState) {
                emit clickedNode(node);
                advanceUserInstructions();
                break;
            }
            emit clickedNodeWithPos(pos, node);
            break;
        }
    }
}

void GraphRepresentation::setInitialAnimation(QQueue<Node*> nodesToColor, QQueue<Edge*> edgesToColor)
{
    for(auto const &e : nodesToColor) {
        QPropertyAnimation *nodeAnim = new QPropertyAnimation(e, "color");
        nodeAnim->setStartValue(QColor(Qt::gray));
        nodeAnim->setDuration(500);
        nodeAnim->setEndValue(QColor(Qt::transparent));
        initialAnimation->addAnimation(nodeAnim);
    }

    for(auto const &e : edgesToColor) {
        QPropertyAnimation *edgeAnim = new QPropertyAnimation(e, "color");
        edgeAnim->setStartValue(QColor(Qt::red));
        edgeAnim->setDuration(500);
        edgeAnim->setEndValue(QColor(Qt::black));
        initialAnimation->addAnimation(edgeAnim);
    }
}

void GraphRepresentation::setAlgorithmAnimationPanel()
{
    userInstructions = new QStackedWidget();

    QLabel *stInstruction = new QLabel("Click on the node which will be the starting vertice for the algorithm");
    stInstruction->setStyleSheet("background:white");

    userInstructions->addWidget(stInstruction);

    QLabel *ndInstruction = new QLabel("Click on the node which will be the ending vertice for the algorithm");
    ndInstruction->setStyleSheet("background:white");

    userInstructions->addWidget(ndInstruction);

    QLabel *rdInstruction = new QLabel;
    rdInstruction->setStyleSheet("background:white");

    userInstructions->addWidget(rdInstruction);

    this->addWidget(userInstructions);
    userInstructions->move(Constants::SCREEN_WIDTH/2 - userInstructions->rect().width()/2,
                           -userInstructions->rect().height()/4);

    userInstructions->hide();

    quitAnimationButton = new QPushButton("Quit Animation");
    this->addWidget(quitAnimationButton);
    quitAnimationButton->move(Constants::SCREEN_WIDTH - quitAnimationButton->rect().width(),
                              Constants::SCREEN_HEIGHT - quitAnimationButton->rect().height());
    quitAnimationButton->hide();
}

void GraphRepresentation::advanceUserInstructions()
{
    userInstructions->setCurrentIndex(userInstructions->currentIndex() + 1);
}

void GraphRepresentation::returnToBuildMode()
{
    userInstructions->hide();
    quitAnimationButton->hide();
    graphToolBar->show();

    initialAnimation->start();

    userInstructions->setCurrentIndex(0);
    animationState = false;
}

void GraphRepresentation::placeGraphicsItem(QGraphicsItem *item)
{
    Edge *edge = dynamic_cast<Edge*>(item);
    Node *node = dynamic_cast<Node*>(item);

    if(edge) {
        if(graph->containsEdge(edge) || edge->startingNode == edge->endingNode) {
            edge->disconnect();
            edge->deleteLater();
            return;
        }
        graph->addEdge(edge);
    }
    else if(node) {
        graph->addNode(node);
    }

    this->addItem(item);
}

void GraphRepresentation::removeGraphicsItem(QGraphicsItem *item)
{
    Edge *edge = dynamic_cast<Edge*>(item);

    if(edge) {
        graph->removeEdge(edge);
    }

    this->removeItem(item);
    delete item;
    item = nullptr;
}

void GraphRepresentation::drawAlgorithmAnimationPanel()
{
    animationState = true;
    graphToolBar->hide();
    this->resetRadioButtons();

    algorithmType aType = static_cast<algorithmType>(algorithmComboBox->currentData().toInt());

    switch(aType) {
        case primsmst:
        case hamcycle:
            break;
        default:
            userInstructions->show();
    }

    quitAnimationButton->show();
}

void GraphRepresentation::showNodeColoringAnimation(QQueue<Node*> nodesToColor, QQueue<Edge*> edgesToColor)
{
    animationState = false;

    setInitialAnimation(nodesToColor, edgesToColor);

    QQueue<Edge*>::const_iterator edgeIte = edgesToColor.constBegin();

    for(auto const &e : nodesToColor) {

        QPropertyAnimation *nodeAnim = new QPropertyAnimation(e, "color");
        nodeAnim->setStartValue(QColor(Qt::transparent));
        nodeAnim->setEndValue(QColor(Qt::gray));
        nodeAnim->setDuration(500);
        nodeColoringAnimation->addAnimation(nodeAnim);

        if(edgeIte != edgesToColor.constEnd()) {
            QPropertyAnimation *edgeAnim = new QPropertyAnimation(*edgeIte, "color");
            edgeAnim->setStartValue(QColor(Qt::black));
            edgeAnim->setEndValue(QColor(Qt::red));
            edgeAnim->setDuration(250);
            nodeColoringAnimation->addAnimation(edgeAnim);

            edgeIte++;
        }
    }
    nodeColoringAnimation->addPause(1000);

    nodeColoringAnimation->start();
}
