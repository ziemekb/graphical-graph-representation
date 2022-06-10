#include <QApplication>
#include "GraphView.h"
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*
    GraphView *graph = new GraphView;
    graph->show();
    */

    MainWindow *mainWindow = new MainWindow;
    mainWindow->show();

    return a.exec();
}
