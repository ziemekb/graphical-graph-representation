#include "Edge.h"
#include <QTextDocument>
#include <QtMath>

graphType Edge::type;

Edge::Edge()
{
    startingNode = nullptr;
    endingNode = nullptr;
    weightText = nullptr;
    weight = 0;
}

Edge::Edge(Node *startingNode, Node *endingNode)
{
    this->setLine(shortenQLineF(startingNode->getCenter(), endingNode->getCenter()));

    this->startingNode = startingNode;
    this->endingNode = endingNode;
    this->weight = 1;

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
    weightText = nullptr;
    if(type == weightedUndirected || type == weightedDirected) {
        this->disconnect();
    }
}

int Edge::getWeight()
{
    return this->weight;
}

void Edge::setWeight(int weight)
{
    this->weight = weight;
    emit weightChangeSignal(this, weight);
}

void Edge::setWeightFromText()
{
    bool ok;

    int tempWeight = weightText->toPlainText().QString::toInt(&ok);

    if(ok) {
        setWeight(tempWeight);
    }
    else {
        weightText->setPlainText(QString::number(this->weight));
    }
}

QLineF Edge::shortenQLineF(QPointF startingPoint, QPointF endingPoint)
{
    QLineF startingLine(startingPoint, endingPoint);
    QLineF endingLine(endingPoint, startingPoint);

    startingLine.setLength(startingLine.length() - Node::nodeHeight/2);
    endingLine.setLength(endingLine.length() - Node::nodeHeight/2);

    return QLineF(startingLine.p2(), endingLine.p2());
}

void Edge::receiveGraphType(graphType type)
{
    this->type = type;
}
