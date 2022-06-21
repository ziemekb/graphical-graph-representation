#include <QGraphicsProxyWidget>
#include <QVector>
#include "MainMenu.h"

MainMenu::MainMenu(QWidget *parent)
{
    this->setSceneRect(0, 0, Constansts::SCREEN_WIDTH, Constansts::SCREEN_HEIGHT);

    createStartingMenu();
    createGraphCreationMenu();

    showStartingMenu();

    connect(startButton, &QPushButton::clicked, this, &MainMenu::showGraphCreationMenu);
    connect(returnButton, &QPushButton::clicked, this, &MainMenu::showStartingMenu);
    connect(returnButton, &QPushButton::clicked, this, &MainMenu::resetRadioButtons);
    connect(createGraphButton, &QPushButton::clicked, this, &MainMenu::clickedCreateGraph);
}


void MainMenu::showGraphCreationMenu()
{
    startButton->hide();
    quitButton->hide();

    createGraphButton->show();
    returnButton->show();
    weightedButton->show();
    unweightedButton->show();
    directedButton->show();
    undirectedButton->show();
}

void MainMenu::showStartingMenu()
{
    createGraphButton->hide();
    returnButton->hide();
    weightedButton->hide();
    unweightedButton->hide();
    directedButton->hide();
    undirectedButton->hide();

    startButton->show();
    quitButton->show();
}

void MainMenu::createStartingMenu()
{
    startButton = new QPushButton("Start");
    quitButton = new QPushButton("Quit");

    proxyWidgetVector.push_back(this->addWidget(startButton));
    proxyWidgetVector.push_back(this->addWidget(quitButton));

    startButton->move(Constansts::SCREEN_WIDTH/2 - startButton->rect().width()/2,
                      Constansts::SCREEN_HEIGHT/2 - startButton->rect().height()/2 - 25);
    quitButton->move(Constansts::SCREEN_WIDTH/2 - quitButton->rect().width()/2,
                     Constansts::SCREEN_HEIGHT/2 - quitButton->rect().height()/2 + 25);
}

void MainMenu::createGraphCreationMenu()
{
    createGraphButton = new QPushButton("create graph");
    returnButton = new QPushButton("return");

    weightedButton = new QRadioButton("weighted");
    unweightedButton = new QRadioButton("unweighted");

    weightButtonGroup = new QButtonGroup;
    weightButtonGroup->addButton(weightedButton);
    weightButtonGroup->addButton(unweightedButton);

    directedButton = new QRadioButton("directed");
    undirectedButton = new QRadioButton("undirected");

    directionButtonGroup = new QButtonGroup;
    directionButtonGroup->addButton(directedButton);
    directionButtonGroup->addButton(undirectedButton);

    proxyWidgetVector.push_back(this->addWidget(weightedButton));
    proxyWidgetVector.push_back(this->addWidget(unweightedButton));
    proxyWidgetVector.push_back(this->addWidget(directedButton));
    proxyWidgetVector.push_back(this->addWidget(undirectedButton));
    proxyWidgetVector.push_back(this->addWidget(createGraphButton));
    proxyWidgetVector.push_back(this->addWidget(returnButton));

    weightedButton->move(Constansts::SCREEN_WIDTH/2 - startButton->rect().width()/2 - 100,
                      Constansts::SCREEN_HEIGHT/2 - startButton->rect().height()/2 - 100);

    unweightedButton->move(Constansts::SCREEN_WIDTH/2 - startButton->rect().width()/2 + 100,
                      Constansts::SCREEN_HEIGHT/2 - startButton->rect().height()/2 - 100);

    directedButton->move(Constansts::SCREEN_WIDTH/2 - startButton->rect().width()/2 - 100,
                      Constansts::SCREEN_HEIGHT/2 - startButton->rect().height()/2 - 50);

    undirectedButton->move(Constansts::SCREEN_WIDTH/2 - startButton->rect().width()/2 + 100,
                      Constansts::SCREEN_HEIGHT/2 - startButton->rect().height()/2 - 50);

    returnButton->move(Constansts::SCREEN_WIDTH/2 - startButton->rect().width()/2 - 100,
                      Constansts::SCREEN_HEIGHT/2 - startButton->rect().height()/2 + 100);

    createGraphButton->move(Constansts::SCREEN_WIDTH/2 - startButton->rect().width()/2 + 100,
                      Constansts::SCREEN_HEIGHT/2 - startButton->rect().height()/2 + 100);
}


void MainMenu::resetRadioButtons()
{
    weightButtonGroup->setExclusive(false);
    directionButtonGroup->setExclusive(false);
    weightedButton->setChecked(false);
    unweightedButton->setChecked(false);
    directedButton->setChecked(false);
    undirectedButton->setChecked(false);
    weightButtonGroup->setExclusive(true);
    directionButtonGroup->setExclusive(true);
}

void MainMenu::clickedCreateGraph()
{
    if(!weightButtonGroup->checkedButton() || !directionButtonGroup->checkedButton()) {
        return;
    }

    if(unweightedButton->isChecked() && undirectedButton->isChecked()) {
        type = unweightedUndirected;
    }
    else if(unweightedButton->isChecked() && directedButton->isChecked()) {
        type = unweightedDirected;
    }
    else if(weightedButton->isChecked() && undirectedButton->isChecked()) {
        type = weightedUndirected;
    }
    else if(weightedButton->isChecked() && directedButton->isChecked()) {
        type = weightedDirected;
    }

    emit createGraphSignal(type);
}

void MainMenu::clearSceneLater()
{
    for(int i = 0; i < proxyWidgetVector.size(); ++i) {
        proxyWidgetVector[i]->deleteLater();
    }
    proxyWidgetVector.clear();

}

QPushButton *MainMenu::getQuitButton() const
{
    return quitButton;
}

QPushButton *MainMenu::getCreateGraphButton() const
{
    return createGraphButton;
}

