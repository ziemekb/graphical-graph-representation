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

public slots:
    void quitDebug();

};


#endif // MAINWINDOW_H
