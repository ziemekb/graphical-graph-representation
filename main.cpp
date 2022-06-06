#include <QApplication>
#include "GraphView.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GraphView *graph = new GraphView;
    graph->show();

    return a.exec();
}
