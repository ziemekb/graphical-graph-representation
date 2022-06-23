#include <QVBoxLayout>
#include <QDebug>
#include <QButtonGroup>
#include <QGraphicsSceneMouseEvent>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QGraphicsSimpleTextItem>
#include "GraphRepresentation.h"
#include "PhantomEdge.h"

bool GraphRepresentation::animationState = false;

GraphRepresentation::GraphRepresentation(const graphType type) {
    this->setSceneRect(0, 0, Constansts::SCREEN_WIDTH, Constansts::SCREEN_HEIGHT);

    this->addItem(buildToolsManager.getDestructionCursor());
    this->addItem(buildToolsManager.getNodeCursor());
    this->addItem(buildToolsManager.getPhantomEdge());

    graph = graphFactory.getGraph(type);

    initialAnimation = new QParallelAnimationGroup;

    generateToolBar(type);

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
    connect(graph, &AbstractGraph::nodesToColorSignal, this, &GraphRepresentation::showNodeColoringAnimation);
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
    graphBuildButtonGroup->setExclusive(false);

    graphBuildButtonGroup->checkedButton()->setChecked(false);

    graphBuildButtonGroup->setExclusive(true);
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
    algorithmComboBox = new QComboBox; // in future this needs to be seperate function with items added depending on the graphType
    //algorithmComboBox->setStyle(...); // algorithmComboBox needs to be changed so that the pop up list always rolls down

    algorithmComboBox->addItem("DFS", dfs);
    algorithmComboBox->addItem("BFS", bfs);
    algorithmComboBox->addItem("Dijkstra's", dijkstra);

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
                break;
            }
            emit clickedNodeWithPos(pos, node);
            break;
        }
    }
}

void GraphRepresentation::setInitialAnimation(Node *node)
{
    for(auto const &e :graph->getKeys()) {
        if(e) {
            QPropertyAnimation *nodeAnim = new QPropertyAnimation(node, "color");
            nodeAnim->setStartValue(node->getColor());
            nodeAnim->setDuration(1000);
            nodeAnim->setEndValue(QColor(Qt::white));
            initialAnimation->addAnimation(nodeAnim);
        }
    }
}

void GraphRepresentation::placeGraphicsItem(QGraphicsItem *item)
{
    Edge *edge = dynamic_cast<Edge*>(item);

    if(edge) {
        graph->addEdge(edge);
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

    userInstructions = new QGraphicsSimpleTextItem("Click on the node which will be starting point for the algorithm");
    this->addItem(userInstructions);
}

void GraphRepresentation::showNodeColoringAnimation(QQueue<Node*> nodesToColor)
{
    nodeColoringAnimation = new QSequentialAnimationGroup;

    for(auto const &e : nodesToColor) {
        Node *node = static_cast<Node*>(e);
        QPropertyAnimation *nodeAnim = new QPropertyAnimation(node, "color");
        nodeAnim->setStartValue(QBrush(Qt::white));
        nodeAnim->setEndValue(QBrush(Qt::gray));
        nodeAnim->setDuration(500);
        nodeColoringAnimation->addAnimation(nodeAnim);
    }
    nodeColoringAnimation->addPause(1000);

    nodeColoringAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}
