#ifndef MAINMENU_H
#define MAINMENU_H

#include <QGraphicsScene>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGroupBox>


class MainMenu : public QWidget {

public:
    MainMenu(QWidget *parent = nullptr);
    void createStartingMenu();
    void createGraphCreationMenu();
    QGraphicsScene* getMainMenuScene() const;

private:
    QGraphicsScene *mainMenuScene;
    QPushButton *startButton;
    QPushButton *quitButton;
};

#endif // MAINMENU_H
