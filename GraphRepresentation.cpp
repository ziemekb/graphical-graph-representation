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
    QToolButton *nodeButton = new QToolButton(graphToolBar);
    QToolButton *edgeButton = new QToolButton(graphToolBar);

    nodeButton->setIcon(QIcon(":/assets/circle_icon.png"));
    edgeButton->setIcon(QIcon(":/assets/edge_icon.png"));

    nodeButton->setCheckable(true);
    edgeButton->setCheckable(true);

    graphToolBar = new QToolBar();

    graphToolBar->addWidget(nodeButton);
    graphToolBar->addWidget(edgeButton);

    graphBuildButtonGroup = new QButtonGroup;

    graphBuildButtonGroup->addButton(nodeButton, nodeButtonID);
    graphBuildButtonGroup->addButton(edgeButton, edgeButtonID);

    graphBuildButtonGroup->setExclusive(true);

    algorithmComboBox = new QComboBox;

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(algorithmComboBox);
    //setLayout(layout);

    algorithmComboBox->addItem("DFS");
    algorithmComboBox->addItem("BFS");
    algorithmComboBox->addItem("Dijkstra's");

    //graphToolBar->setLayout(layout);
    graphToolBar->addWidget(algorithmComboBox);

    this->scene->addWidget(graphToolBar);
}

QGraphicsScene *GraphRepresentation::getScene() const
{
    return scene;
}

