#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsView>
#include <QGraphicsScene>

class MainMenu;
class GraphRepresentation;

enum graphType {
    unweightedUndirected,
    weightedUndirected,
    unweightedDirected,
    weightedDirected
};

namespace Constansts {
        inline constexpr int SCREEN_WIDTH = 800;
        inline constexpr int SCREEN_HEIGHT = 600;
};


class MainWindow : public QGraphicsView {
Q_OBJECT

public:
    MainWindow();

private:
    MainMenu *mainMenu;
    GraphRepresentation *graphRep;

public slots:
    void changeToGraphScene(graphType type);
};


#endif // MAINWINDOW_H
