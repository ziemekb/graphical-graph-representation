#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include "Node.h"
#include "MainWindow.h"
#include "WeightText.h"

class Edge : public QObject, public QGraphicsLineItem {
    Q_OBJECT
    Q_PROPERTY(QColor color READ getColor WRITE setColor)
public:
    Edge();
    Edge(Node *startingNode, Node *endingNode);
    ~Edge();

    Node *startingNode;
    Node *endingNode;

    int getWeight();
    void setPen(const QPen &pen);

    void setColor(QColor color);
    QColor getColor();

private:
    static graphType type;
    int weight;
    WeightText *weightText;
    void setWeightFromText();

    QLineF shortenQLineF(QPointF startingPoint, QPointF endingPoint);

    const static qreal arrowAngle;
    const static qreal arrowLength;
    QGraphicsLineItem *leftArrow;
    QGraphicsLineItem *rightArrow;

public slots:
    void receiveGraphType(graphType type);
    void setWeight(int weight);
};

#endif // EDGE_H
