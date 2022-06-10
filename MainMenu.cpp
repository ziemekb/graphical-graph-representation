#include "MainMenu.h"
#include "GraphView.h"
#include <QGraphicsProxyWidget>


MainMenu::MainMenu(QWidget *parent) : QWidget(parent)
{
    mainMenuScene = new QGraphicsScene;
    mainMenuScene->setSceneRect(0, 0, GraphView::SCREEN_WIDTH, GraphView::SCREEN_HEIGHT);
    createStartingMenu();
}

void MainMenu::createStartingMenu()
{
    startButton = new QPushButton("Start");
    quitButton = new QPushButton("Quit");

    mainMenuScene->addWidget(startButton);
    mainMenuScene->addWidget(quitButton);

    startButton->move(GraphView::SCREEN_WIDTH/2 - startButton->rect().width()/2,
                      GraphView::SCREEN_HEIGHT/2 - startButton->rect().height()/2 - 25);
    quitButton->move(GraphView::SCREEN_WIDTH/2 - quitButton->rect().width()/2,
                      GraphView::SCREEN_HEIGHT/2 - quitButton->rect().height()/2 + 25);
}

QGraphicsScene *MainMenu::getMainMenuScene() const
{
    return mainMenuScene;
}

