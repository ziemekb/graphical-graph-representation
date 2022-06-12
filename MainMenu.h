#ifndef MAINMENU_H
#define MAINMENU_H

#include <QGraphicsScene>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QVector>
#include "MainWindow.h"

class MainMenu : public QWidget {
Q_OBJECT

public:
    MainMenu(QWidget *parent = nullptr);
    QGraphicsScene* getMainMenuScene() const;
    QPushButton* getQuitButton() const;
    QPushButton* getCreateGraphButton() const;

public slots:
    void showStartingMenu();
    void showGraphCreationMenu();
    void resetRadioButtons();
    void clickedCreateGraph();

signals:
    void createGraphSignal(graphType graphType);

private:
    QGraphicsScene *mainMenuScene;

    void createGraphCreationMenu();
    void createStartingMenu();

    //Starting menu buttons
    QPushButton *startButton;
    QPushButton *quitButton;

    //Group and buttons for managing whether graph is weighted or not
    QButtonGroup *weightButtonGroup;
    QRadioButton *weightedButton;
    QRadioButton *unweightedButton;

    //Group and buttons for managing whether graph is directed or not
    QButtonGroup *directionButtonGroup;
    QRadioButton *directedButton;
    QRadioButton *undirectedButton;

    //Graph creation menu buttons
    QPushButton *createGraphButton;
    QPushButton *returnButton;

    graphType type;
    //useless for now
    QVector<QGraphicsProxyWidget*> proxyWidgetVector;
    void clearSceneLater();
};

#endif // MAINMENU_H
