#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsView>
#include "MainMenu.h"
#include <QGraphicsScene>

class MainWindow : public QGraphicsView {

public:
    MainWindow();

private:
    MainMenu *mainMenu;
};


#endif // MAINWINDOW_H
