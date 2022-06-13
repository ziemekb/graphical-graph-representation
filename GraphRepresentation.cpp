#include <GraphView.h>
#include <QVBoxLayout>>
#include "GraphRepresentation.h"

GraphRepresentation::GraphRepresentation(const graphType type) {
    scene = new QGraphicsScene;
    scene->setSceneRect(0, 0, Constansts::SCREEN_WIDTH, Constansts::SCREEN_HEIGHT);

    generateToolBar(type);
}

void GraphRepresentation::generateToolBar(const graphType type)
{
    //Adding buttons associated with graph creation
    QToolButton *nodeButton = new QToolButton(graphToolBar);
    QToolButton *edgeButton = new QToolButton(graphToolBar);

    nodeButton->setIcon(QIcon(":/assets/circle_icon.png"));
    edgeButton->setIcon(QIcon(":/assets/edge_icon.png"));

    nodeButton->setCheckable(true);
    edgeButton->setCheckable(true);

    //Organizing buttons in a button group
    graphBuildButtonGroup = new QButtonGroup;

    graphBuildButtonGroup->addButton(nodeButton, nodeButtonID);
    graphBuildButtonGroup->addButton(edgeButton, edgeButtonID);

    //Adding buttons to QToolBar
    graphToolBar = new QToolBar();

    graphToolBar->addWidget(nodeButton);
    graphToolBar->addWidget(edgeButton);

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

    this->scene->addWidget(graphToolBar);
}

QGraphicsScene *GraphRepresentation::getScene() const
{
    return scene;
}

