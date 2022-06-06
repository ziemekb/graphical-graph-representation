#include "Graph.h"
#include "GraphView.h"

void Graph::addEdge(Node* node1, Node* node2)
{
    int node1Val = node1->data(nodeType).value<int>();
    int node2Val = node2->data(nodeType).value<int>();

    for(int i = 0; i < adjList[node1->data(nodeType).value<int>()].size(); ++i) {
        if(adjList[node1Val][i]->data(nodeType).value<int>() == node2Val) {
            return;
        }
    }

    adjList[node1Val].push_back(node2);
    adjList[node2Val].push_back(node1);
}

void Graph::addNode()
{
    adjList.push_back(QVector<Node*>());
}

void Graph::DFS(Node* startingNode, Node* soughtNode)
{
    visited[startingNode] = true;

    //emit checkedNode(startingNode);
    nodesToColor.enqueue(startingNode);

    if(startingNode == soughtNode) {
        qDebug() << "Found the node";
        emit endOfDFS(nodesToColor);
        nodesToColor.clear();
        return;
    }

    for(auto const &e : adjList[startingNode->data(nodeType).value<int>()]) {
        if(!visited[e]) {
           this->DFS(e, soughtNode);
        }
    }
}
