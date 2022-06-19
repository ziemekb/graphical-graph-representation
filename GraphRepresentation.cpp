#include <QVBoxLayout>
#include <QDebug>
#include <QButtonGroup>
#include <QGraphicsSceneMouseEvent>
#include "GraphRepresentation.h"

GraphRepresentation::GraphRepresentation(const graphType type) {
    this->setSceneRect(0, 0, Constansts::SCREEN_WIDTH, Constansts::SCREEN_HEIGHT);

    connect(buildToolsManager.getNodeCursor(), &NodeCursor::nodeToBePlaced, this, &GraphRepresentation::placeGraphicsItem);

    this->addItem(buildToolsManager.getDestructionCursor()->getCursor());
    this->addItem(buildToolsManager.getNodeCursor());

    generateToolBar(type);
}

void GraphRepresentation::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    buildToolsManager.update(static_cast<buttonID>(graphBuildButtonGroup->checkedId()), event->scenePos());

    QGraphicsScene::mouseMoveEvent(event);
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
    destroyButton->setIcon(QIcon(":/assets/hammer_icon.png"));

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

    algorithmComboBox->addItem("DFS");
    algorithmComboBox->addItem("BFS");
    algorithmComboBox->addItem("Dijkstra's");

    graphToolBar->addWidget(algorithmComboBox);

    graphToolBar->addSeparator();

    //Adding start algorithm button
    startAlgorithmButton = new QPushButton("Start algorithm");

    graphToolBar->addWidget(startAlgorithmButton);

    this->addWidget(graphToolBar);
}

void GraphRepresentation::placeGraphicsItem(QGraphicsItem *item)
{
    this->addItem(item);
}
