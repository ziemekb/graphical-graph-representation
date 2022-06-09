#ifndef GRAPH_H
#define GRAPH_H

#include <QQueue>
#include "Node.h"
#include "Edge.h"
#include <QHash>

enum dataType {
    nodeType,
    edgeType
};

class Graph : public QObject {
Q_OBJECT
public:
    QHash<Node*, QHash<Node*, int>> adjList;

    void addEdge(Node* node1, Node* node2);
    void addEdge(Edge *edge);
    void addNode();
    void DFS(Node* firstNode, Node* searchedNode);

signals:
    void endOfDFS(QQueue<Node*> nodesToColor);

private:
    QMap <Node*, bool> visited;
    QQueue<Node*> nodesToColor;
};

inline bool operator==(const Node &node1, const Node &node2)
{
    return node1.data(nodeType).value<int>() == node2.data(nodeType).value<int>();
}

inline uint qHash(const Node &key)
{
    return key.data(nodeType).value<int>();
}


#endif // GRAPH_H
