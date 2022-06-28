#include "Edge.h"
#include <QTextDocument>
#include <QtMath>

Edge *Edge::createEdge(Node *startingNode, Node *endingNode, const graphType type)
{
    switch(type) {
        case unweightedUndirected:
            return new Edge(startingNode, endingNode, false, false);
        break;

        case unweightedDirected:
            return new Edge(startingNode, endingNode, false, true);
        break;

        case weightedUndirected:
            return new Edge(startingNode, endingNode, true, false);
        break;

        case weightedDirected:
            return new Edge(startingNode, endingNode, true, true);
        break;

        default:
            return new Edge();
    }
}

Edge::Edge()
{
    startingNode = nullptr;
    endingNode = nullptr;
    weight = 0;
}

Edge::Edge(Node *startingNode, Node *endingNode, bool weighted, bool directed)
{
    this->setLine(QLineF(startingNode->getCenter(), endingNode->getCenter()));
    this->startingNode = startingNode;
    this->endingNode = endingNode;
    this->weight = 1;


    if(weighted) {
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
    if(directed) {
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
