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
    dijkstras,
    primsmst
};

class AbstractGraph : public QObject {
Q_OBJECT
public:
    AbstractGraph();
    virtual void addEdge(Node* node1, Node* node2) = 0;
    virtual void addEdge(Edge *edge) = 0;
    virtual void removeEdge(Edge *edge) = 0;
    void addNode(Node *node);
    bool containsEdge(Edge *edge);
    void DFS(Node* firstNode, Node* searchedNode);
    void BFS(Node* firstNode, Node* searchedNode);
    void dijkstra(Node* firstNode, Node* secondNode);
    void primMST();
    QList<Node*> getKeys();

signals:
    void nodesToColorSignal(QQueue<Node*> nodesToColor);
public slots:
    void receiveNode(Node *node);
    void getAlgorithmType(algorithmType aType);

protected:
    QHash<Node*, QHash<Node*, int>> adjList;
    QMap <Node*, bool> visited;
    QQueue<Node*> nodesToColor;
    Node *algorithmStartingNode;
    Node *algorithmEndingNode;
    algorithmType aType;

private:
    void resetVisited();
    void reverseQueue(QQueue<Node*> &queue);
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
