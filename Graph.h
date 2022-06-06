#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"
#include <QQueue>

class Graph : public QObject {
Q_OBJECT
public:
    QVector<QVector<Node*>> adjList;

    void addEdge(Node* node1, Node* node2);
    void addNode();
    void DFS(Node* firstNode, Node* searchedNode);

signals:
    void endOfDFS(QQueue<Node*> nodesToColor);

private:
    QMap <Node*, bool> visited;
    QQueue<Node*> nodesToColor;
};

#endif // GRAPH_H
