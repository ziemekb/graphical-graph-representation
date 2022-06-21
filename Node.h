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

    int nodeNumber;
    QPointF center;

    void setCenter(const QPointF &center);
    void setColor(QColor color);

    bool doesCollide();

    ~Node();

};

#endif // NODE_H
