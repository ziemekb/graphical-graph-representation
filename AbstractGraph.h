#ifndef ABSTRACTGRAPH_H
#define ABSTRACTGRAPH_H

#include <QQueue>
#include <QHash>
#include "Node.h"
#include "Edge.h"

enum dataType {
    nodeType,
    edgeType
};

enum algorithmType {
    dfs,
    bfs,
    dijkstra
};

class AbstractGraph : public QObject {
Q_OBJECT
public:
    virtual void addEdge(Node* node1, Node* node2) = 0;
    virtual void addEdge(Edge *edge) = 0;
    virtual void removeEdge(Edge *edge) = 0;
    void runAlgorithm(algorithmType aType);
    void DFS(Node* firstNode, Node* searchedNode);
    QList<Node*> getKeys();

signals:
    void nodesToColorSignal(QQueue<Node*> nodesToColor);

protected:
    QHash<Node*, QHash<Node*, int>> adjList;
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

#endif // ABSTRACTGRAPH_H
