#include "MainWindow.h"
#include <QDebug>

MainWindow::MainWindow()
{
    mainMenu = new MainMenu;
    this->setScene(mainMenu->getMainMenuScene());

    connect(mainMenu->getQuitButton(), &QPushButton::clicked, this, &MainWindow::close);
}


