#include "MainWindow.h"
#include "MainMenu.h"
#include "GraphRepresentation.h"
#include <QDebug>

MainWindow::MainWindow()
{
    mainMenu = new MainMenu;

    this->setScene(mainMenu->getMainMenuScene());

    connect(mainMenu->getQuitButton(), &QPushButton::clicked, this, &MainWindow::close);
    connect(mainMenu, &MainMenu::createGraphSignal, this, &MainWindow::changeToGraphScene);
}

void MainWindow::changeToGraphScene(graphType graphType)
{
    graphRep = new GraphRepresentation(graphType);
    this->setScene(graphRep->getScene());
}


