#include <QTextDocument>
#include <QtMath>
#include <QTextCharFormat>
#include <QTextCursor>
#include <QPainter>
#include "Edge.h"

graphType Edge::type;
const qreal Edge::arrowAngle = 30;
const qreal Edge::arrowLength = 20;

Edge::Edge()
{
    startingNode = nullptr;
    endingNode = nullptr;
    weightText = nullptr;
    leftArrow = nullptr;
    rightArrow = nullptr;
    weight = 0;
}

Edge::Edge(Node *startingNode, Node *endingNode)
{
    this->setLine(shortenQLineF(startingNode->getCenter(), endingNode->getCenter()));

    this->startingNode = startingNode;
    this->endingNode = endingNode;
    this->weight = 1;

    if(type == weightedUndirected || type == weightedDirected) {
        weightText = new WeightText(this);
        weightText->setPos(qFabs(startingNode->getCenter().x() + endingNode->getCenter().x())/2 - weightText->boundingRect().width()/2,
                           qFabs(startingNode->getCenter().y() + endingNode->getCenter().y())/2 - weightText->boundingRect().height()/2);
        connect(weightText, &WeightText::weightChange, this, &Edge::setWeight);
    }
    else {
        weightText = nullptr;
    }

    if(type == weightedDirected || type == unweightedDirected) {

        paintArc();

        leftArrow = new QGraphicsLineItem(this);
        rightArrow = new QGraphicsLineItem(this);

        QLineF line;
        line.setP1(this->line().p1());
        line.setLength(arrowLength);
        line.setAngle(this->line().angle() - arrowAngle);

        leftArrow->setLine(line);

        line.setAngle(this->line().angle() + arrowAngle);

        rightArrow->setLine(line);
    }
    else {
        leftArrow = nullptr;
        rightArrow = nullptr;
    }

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
}

void Edge::setPen(const QPen &pen)
{
    QGraphicsLineItem::setPen(pen);

    if(weightText) {
        weightText->setDefaultTextColor(pen.color());
    }

    if(leftArrow && rightArrow) {
        leftArrow->setPen(pen);
        rightArrow->setPen(pen);
    }
}

void Edge::setColor(QColor color)
{
    this->setPen(color);

    if(leftArrow && rightArrow) {
        leftArrow->setPen(color);
        rightArrow->setPen(color);
    }
}

QColor Edge::getColor()
{
    return this->pen().color();
}

void Edge::paintArc()
{
    QLineF shortLine(shortenQLineF(startingNode->getCenter(), endingNode->getCenter()));
    QPointF betweenPoint(qFabs(shortLine.p1().x() + shortLine.p2().x()) / 2,
                         qFabs(shortLine.p1().y() + shortLine.p2().y()) / 2);

    qreal distance = shortLine.length();
    qreal radius = (distance / 2.0) / qSin(qDegreesToRadians(static_cast<double>(30)));
    qreal diagonal = qSqrt(radius * radius - distance * distance / 4);

    qreal x_a = betweenPoint.x() - shortLine.p1().x();
    qreal y_a = betweenPoint.y() - shortLine.p1().y();

    QPointF center(betweenPoint.x() + y_a * (diagonal/distance),
                   betweenPoint.y() - x_a * (diagonal/distance));

    QPointF cornerPoint(center.x() + radius, center.y() + radius);

    QRectF rect(cornerPoint.x(), cornerPoint.y(), 2 * radius, 2 * radius);

    int startAngle = 16 * QLineF(shortLine.p1(), center).angle();
    int spanAngle = 16 * 30;

    QPainter painter;
    painter.drawArc(rect, startAngle, spanAngle);
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
