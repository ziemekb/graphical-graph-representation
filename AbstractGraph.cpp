#include "AbstractGraph.h"

AbstractGraph::AbstractGraph()
{
    algorithmStartingNode = nullptr;
    algorithmEndingNode = nullptr;
}

void AbstractGraph::addNode(Node *node)
{
    adjList[node];
}

bool AbstractGraph::containsEdge(Edge *edge)
{
    return adjList[edge->startingNode].contains(edge->endingNode);
}

void AbstractGraph::DFS(Node* startingNode, Node* soughtNode)
{
    visited[startingNode] = true;

    nodesToColor.enqueue(startingNode);

    if(startingNode == soughtNode) {
        emit nodesToColorSignal(nodesToColor);
    }
    else {
        QHash<Node*, int>::const_iterator i;

        for(i  = adjList[startingNode].constBegin(); i != adjList[startingNode].constEnd(); ++i) {
            if(!visited[i.key()]) {
                this->DFS(i.key(), soughtNode);
            }
        }
    }
}

void AbstractGraph::BFS(Node *startingNode, Node *soughtNode)
{
    std::queue<Node*> queue;

    queue.push(startingNode);

    Node *frontNode;

    while(!queue.empty()) {

        frontNode = queue.front();
        nodesToColor.enqueue(frontNode);

        if(frontNode == soughtNode) {
            emit nodesToColorSignal(nodesToColor);
            return;
        }
        visited[frontNode] = true;
        queue.pop();

        QHash<Node*, int>::const_iterator i;

        for(i  = adjList[frontNode].constBegin(); i != adjList[frontNode].constEnd(); ++i) {
            if(!visited[i.key()]) {
                queue.push(i.key());
                visited[i.key()] = true;
            }
        }
    }
}

void AbstractGraph::dijkstra(Node *firstNode, Node *secondNode)
{
    std::vector<std::pair<Node*, int>> nodes;

    for(auto const &e : this->getKeys()) {
        if(e == firstNode) {
            nodes.push_back(std::make_pair(e, 0));
        }
        else {
            nodes.push_back(std::make_pair(e, INT_MAX));
        }
    }
    auto distanceComparator = [] (std::pair<Node*, int> firstPair, std::pair<Node*, int> secondPair) {
        return firstPair.second > secondPair.second;
    };

    std::priority_queue<std::pair<Node*, int>, std::vector<std::pair<Node*, int>>,
            decltype(distanceComparator)> pq(nodes.begin(), nodes.end(), distanceComparator);

    while(!pq.empty()) {
        qDebug() << pq.top().first->data(nodeType).value<int>() << pq.top().second;
        pq.pop();
    }
}

QList<Node*> AbstractGraph::getKeys()
{
    return adjList.keys();
}

void AbstractGraph::receiveNode(Node *node)
{
    if(!algorithmStartingNode) {
        algorithmStartingNode = node;
        return;
    }

    algorithmEndingNode = node;

    switch(aType) {
    case dfs:
        this->DFS(algorithmStartingNode, algorithmEndingNode);
        break;
    case bfs:
        this->BFS(algorithmStartingNode, algorithmEndingNode);
        break;
    case dijkstras:
        this->dijkstra(algorithmStartingNode, algorithmEndingNode);
        break;
    default:
        qDebug() << "unknown algorithm type";
        break;
    }

    algorithmStartingNode = nullptr;
    algorithmEndingNode = nullptr;
    resetVisited();
    nodesToColor.clear();
}

void AbstractGraph::getAlgorithmType(algorithmType aType)
{
    this->aType = aType;
}

void AbstractGraph::resetVisited()
{
    for(auto const &e : getKeys()) {
        visited[e] = false;
    }
}
