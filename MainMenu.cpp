#include "MainMenu.h"
#include "GraphView.h"
#include <QGraphicsProxyWidget>
#include <QVector>


MainMenu::MainMenu(QWidget *parent) : QWidget(parent)
{
    mainMenuScene = new QGraphicsScene;
    mainMenuScene->setSceneRect(0, 0, GraphView::SCREEN_WIDTH, GraphView::SCREEN_HEIGHT);

    createStartingMenu();
}

void MainMenu::createStartingMenu()
{
    clearSceneLater();

    startButton = new QPushButton("Start");
    quitButton = new QPushButton("Quit");

    proxyWidgetVector.push_back(mainMenuScene->addWidget(startButton));
    proxyWidgetVector.push_back(mainMenuScene->addWidget(quitButton));

    startButton->move(GraphView::SCREEN_WIDTH/2 - startButton->rect().width()/2,
                      GraphView::SCREEN_HEIGHT/2 - startButton->rect().height()/2 - 25);
    quitButton->move(GraphView::SCREEN_WIDTH/2 - quitButton->rect().width()/2,
                     GraphView::SCREEN_HEIGHT/2 - quitButton->rect().height()/2 + 25);

    connect(startButton, &QPushButton::clicked, this, &MainMenu::createGraphCreationMenu);
}

void MainMenu::createGraphCreationMenu()
{
    clearSceneLater();

    createGraphButton = new QPushButton("create graph");
    returnButton = new QPushButton("return");

    weightedButton = new QRadioButton("weighted");
    unweightedButton = new QRadioButton("unweighted");

    weightButtonGroup = new QButtonGroup;
    weightButtonGroup->addButton(weightedButton);
    weightButtonGroup->addButton(unweightedButton);

    directedButton = new QRadioButton("directed");
    undirectedButton = new QRadioButton("undirected");

    directionButtonGroup = new QButtonGroup;
    directionButtonGroup->addButton(directedButton);
    directionButtonGroup->addButton(undirectedButton);

    proxyWidgetVector.push_back(mainMenuScene->addWidget(weightedButton));
    proxyWidgetVector.push_back(mainMenuScene->addWidget(unweightedButton));
    proxyWidgetVector.push_back(mainMenuScene->addWidget(directedButton));
    proxyWidgetVector.push_back(mainMenuScene->addWidget(undirectedButton));
    proxyWidgetVector.push_back(mainMenuScene->addWidget(createGraphButton));
    proxyWidgetVector.push_back(mainMenuScene->addWidget(returnButton));

    weightedButton->move(GraphView::SCREEN_WIDTH/2 - startButton->rect().width()/2 - 100,
                      GraphView::SCREEN_HEIGHT/2 - startButton->rect().height()/2 - 100);

    unweightedButton->move(GraphView::SCREEN_WIDTH/2 - startButton->rect().width()/2 + 100,
                      GraphView::SCREEN_HEIGHT/2 - startButton->rect().height()/2 - 100);

    directedButton->move(GraphView::SCREEN_WIDTH/2 - startButton->rect().width()/2 - 100,
                      GraphView::SCREEN_HEIGHT/2 - startButton->rect().height()/2 - 50);

    undirectedButton->move(GraphView::SCREEN_WIDTH/2 - startButton->rect().width()/2 + 100,
                      GraphView::SCREEN_HEIGHT/2 - startButton->rect().height()/2 - 50);

    returnButton->move(GraphView::SCREEN_WIDTH/2 - startButton->rect().width()/2 - 100,
                      GraphView::SCREEN_HEIGHT/2 - startButton->rect().height()/2 + 100);

    createGraphButton->move(GraphView::SCREEN_WIDTH/2 - startButton->rect().width()/2 + 100,
                      GraphView::SCREEN_HEIGHT/2 - startButton->rect().height()/2 + 100);

    connect(returnButton, &QPushButton::clicked, this, &MainMenu::createStartingMenu);
}

void MainMenu::clearSceneLater()
{
    for(int i = 0; i < proxyWidgetVector.size(); ++i) {
        proxyWidgetVector[i]->deleteLater();
    }
    proxyWidgetVector.clear();

}

QGraphicsScene *MainMenu::getMainMenuScene() const
{
    return mainMenuScene;
}

QPushButton *MainMenu::getQuitButton() const
{
    return quitButton;
}

