#include "MainWindow.h"
#include "MainMenu.h"
#include "GraphRepresentation.h"
#include <QDebug>

MainWindow::MainWindow()
{
    mainMenu = new MainMenu;

    this->setScene(mainMenu);

    connect(mainMenu->getQuitButton(), &QPushButton::clicked, this, &MainWindow::close);
    connect(mainMenu, &MainMenu::createGraphSignal, this, &MainWindow::changeToGraphScene);
}

void MainWindow::changeToGraphScene(graphType type)
{
    graphRep = new GraphRepresentation(type);
    this->setScene(graphRep);
}


