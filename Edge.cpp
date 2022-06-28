#include "Edge.h"
#include <QTextDocument>
#include <QtMath>

Edge::Edge()
{
    startingNode = nullptr;
    endingNode = nullptr;
    weight = 0;
}

Edge::Edge(Node *startingNode, Node *endingNode, int weight)
{
    this->setLine(QLineF(startingNode->getCenter(), endingNode->getCenter()));
    this->startingNode = startingNode;
    this->endingNode = endingNode;
    this->weight = weight;


    weightText = new QGraphicsTextItem(this);
    weightText->setPlainText(QString::number(weight));
    weightText->setTextInteractionFlags(Qt::TextEditorInteraction);
    weightText->setPos(qFabs(startingNode->getCenter().x() + endingNode->getCenter().x())/2,
                       qFabs(startingNode->getCenter().y() + endingNode->getCenter().y())/2 - 25);

    connect(weightText->document(), &QTextDocument::contentsChanged, this, &Edge::setWeightFromText);
}

Edge::~Edge()
{
    startingNode = nullptr;
    endingNode = nullptr;
}


int Edge::getWeight()
{
    return this->weight;
}

void Edge::setWeight(int weight)
{
    this->weight = weight;
}

void Edge::setWeightFromText()
{
    bool ok;

    int tempWeight = weightText->toPlainText().QString::toInt(&ok);

    if(ok) {
        this->weight = tempWeight;
    }
    else {
        weightText->setPlainText(QString::number(this->weight));
    }
}
