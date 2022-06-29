#include "Edge.h"
#include <QTextDocument>
#include <QtMath>

graphType Edge::type;

Edge::Edge()
{
    startingNode = nullptr;
    endingNode = nullptr;
    weight = 0;
}

Edge::Edge(Node *startingNode, Node *endingNode)
{
    this->setLine(QLineF(startingNode->getCenter(), endingNode->getCenter()));
    this->startingNode = startingNode;
    this->endingNode = endingNode;
    this->weight = 1;

    qDebug() << type;

    if(type == weightedUndirected || type == weightedDirected) {
        weightText = new QGraphicsTextItem(this);
        weightText->setPlainText(QString::number(weight));
        weightText->setTextInteractionFlags(Qt::TextEditorInteraction);
        weightText->setPos(qFabs(startingNode->getCenter().x() + endingNode->getCenter().x())/2,
                           qFabs(startingNode->getCenter().y() + endingNode->getCenter().y())/2 - 25);
        connect(weightText->document(), &QTextDocument::contentsChanged, this, &Edge::setWeightFromText);
    }
    else {
        weightText = nullptr;
    }
    /*
    if(type == weightedDirected || type == unweightedDirected) {
        arrow = new ...
    }
    else {

    }
    */
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

void Edge::receiveGraphType(graphType type)
{
    this->type = type;
}
