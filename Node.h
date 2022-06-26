#ifndef NODE_H
#define NODE_H

#include <QObject>
#include <QGraphicsEllipseItem>
#include <QPointF>
#include <QBrush>
#include <queue>

class Node : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT
    Q_PROPERTY(QColor color READ getColor WRITE setColor)
public:
    static int nodeCount;
    static constexpr int nodeWidth = 75;
    static constexpr int nodeHeight = 75;

    Node();
    Node(QPointF center);
    void mousePressEvene(QGraphicsSceneMouseEvent *event);

    void setCenter(const QPointF &center);
    QPointF getCenter();

    void setColor(QColor color);
    QColor getColor();

    ~Node();

private:
    static std::priority_queue<int, std::vector<int>, std::greater<int>> unusedNodeNumbers;
    int nodeNumber;
    QPointF center;
    QColor color;
};

#endif // NODE_H
