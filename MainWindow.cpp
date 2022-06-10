#include "MainWindow.h"
#include <QDebug>

MainWindow::MainWindow()
{
    mainMenu = new MainMenu;
    this->setScene(mainMenu->getMainMenuScene());

    connect(mainMenu->getQuitButton(), &QPushButton::clicked, this, &MainWindow::quitDebug);
}

void MainWindow::quitDebug()
{
    qDebug() << "should be closing now";
    this->close();
}

