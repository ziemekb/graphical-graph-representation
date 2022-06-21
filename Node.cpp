#include "Node.h"
#include "GraphView.h"
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

Node::Node(QPointF center) {
    setPen(QPen(Qt::black));
    setRect(0, 0, nodeWidth, nodeHeight);
    this->setCenter(center);

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

bool Node::doesCollide()
{
    QList<QGraphicsItem*> collidingItems = scene()->collidingItems(this);

    for(auto const &e : collidingItems) {
        if(typeid(*e) == typeid(Node)) {
            qDebug() << "colliding node";
            return true;
        }
        else if (typeid(*e) == typeid(QGraphicsSimpleTextItem)) {}
        else if(typeid(*e) != typeid(QGraphicsEllipseItem)) {
            qDebug() << "colliding object";
            return true;
        }
    }
    return false;
}

void Node::setCenter(const QPointF &center)
{
    this->center = center;
}

void Node::setColor(QColor color)
{
    //setPen(QPen(color)); //this sets the circumference color
    setBrush(color);       //this sets the inside color
}

Node::~Node()
{
    unusedNodeNumbers.push(this->nodeNumber);

    nodeCount--;
}

