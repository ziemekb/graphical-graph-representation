#ifndef MAINMENU_H
#define MAINMENU_H

#include <QGraphicsScene>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QVector>

class MainMenu : public QWidget {

public:
    MainMenu(QWidget *parent = nullptr);
    void createStartingMenu();
    QGraphicsScene* getMainMenuScene() const;
    QPushButton* getQuitButton() const;

public slots:
    void createGraphCreationMenu();

private:
    QGraphicsScene *mainMenuScene;

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

    QPushButton *createGraphButton;
    QPushButton *returnButton;

    QVector<QGraphicsProxyWidget*> proxyWidgetVector;
    void clearSceneLater();
};

#endif // MAINMENU_H
