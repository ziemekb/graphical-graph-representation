#ifndef NODE_H
#define NODE_H

#include <QObject>
#include <QGraphicsEllipseItem>
#include <QPointF>
#include <queue>

class Node : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT
    Q_PROPERTY(QColor color WRITE setColor)
public:
    static int nodeCount;
    static constexpr int nodeWidth = 75;
    static constexpr int nodeHeight = 75;

    Node();
    Node(QPointF center);

    void setCenter(const QPointF &center);
    QPointF getCenter();
    void setColor(QColor color);

    ~Node();

private:
    static std::priority_queue<int, std::vector<int>, std::greater<int>> unusedNodeNumbers;
    int nodeNumber;
    QPointF center;
};

#endif // NODE_H
