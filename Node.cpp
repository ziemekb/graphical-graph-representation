#include "Node.h"
#include "AbstractGraph.h"
#include <QList>
#include <QGraphicsItem>
#include <QDebug>
#include <QPen>

int Node::nodeCount = 0;
std::priority_queue<int, std::vector<int>, std::greater<int>> Node::unusedNodeNumbers;


Node::Node() {
    setPen(QPen(Qt::black));
    setRect(0, 0, nodeWidth, nodeHeight);

    Node::nodeCount++;

    if(!unusedNodeNumbers.empty()) {
        nodeNumber = unusedNodeNumbers.top();
        unusedNodeNumbers.pop();
    }
    else {
        nodeNumber = nodeCount;
    }

    setData(nodeType, nodeNumber);

    QGraphicsSimpleTextItem *nodeTextNumber = new QGraphicsSimpleTextItem();
    nodeTextNumber->setText(QString::number(nodeNumber));
    nodeTextNumber->setPos(this->rect().width()/2-nodeTextNumber->boundingRect().width()/2,
                           this->rect().height()/2-nodeTextNumber->boundingRect().height()/2);

    nodeTextNumber->setParentItem(this);
}

Node::Node(QPointF center) : Node() {
    this->setCenter(center);
}

void Node::setCenter(const QPointF &center)
{
    this->center = center;
}

QPointF Node::getCenter()
{
    return center;
}

void Node::setColor(QColor color)
{
    //setPen(QPen(color)); //this sets the circumference color
    setBrush(color);       //this sets the inside color
    this->color = color;
}

QColor Node::getColor()
{
    return color;
}

Node::~Node()
{
    unusedNodeNumbers.push(this->nodeNumber);

    nodeCount--;
}

