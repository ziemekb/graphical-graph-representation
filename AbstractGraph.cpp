#include <QStack>
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
        QHash<Node*, Edge*>::const_iterator i;

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

        QHash<Node*, Edge*>::const_iterator i;

        for(i  = adjList[frontNode].constBegin(); i != adjList[frontNode].constEnd(); ++i) {
            if(!visited[i.key()]) {
                queue.push(i.key());
                visited[i.key()] = true;
            }
        }
    }
}

void AbstractGraph::dijkstra(Node *startingNode, Node *soughtNode)
{
    //creating a priority queue and adding startingNode to it with distance 0
    auto distanceComparator = [] (std::pair<Node*, int> firstPair, std::pair<Node*, int> secondPair) {
        return firstPair.second > secondPair.second;
    };

    std::priority_queue<std::pair<Node*, int>, std::vector<std::pair<Node*, int>>,
            decltype(distanceComparator)> pq(distanceComparator);

    pq.push(std::make_pair(startingNode, 0));


    //creating distance hash table and assigning maximal value to every node except startingNode
    QHash<Node*, int> dist;

    for(auto const &e : this->getKeys()) {
        dist[e] = INT_MAX;
    }

    dist[startingNode] = 0;

    //hash table for tracking parents of nodes
    QHash<Node*, Node*> parent;

    //main dijkstra loop
    while(!pq.empty()) {

        Node *topNode = pq.top().first;
        pq.pop();

        QHash<Node*, Edge*>::const_iterator i;

        for(i = adjList[topNode].constBegin(); i != adjList[topNode].constEnd(); ++i) {

            if(dist[i.key()] > dist[topNode] + i.value()->getWeight()) {
                dist[i.key()] = dist[topNode] + i.value()->getWeight();
                pq.push(std::make_pair(i.key(), dist[i.key()]));
                parent[i.key()] = topNode;
            }
        }
    }

    //finding shortest path from startingNode to soughtNode
    Node *node = soughtNode;
    nodesToColor.enqueue(node);

    while(node != startingNode) {
        node = parent[node];
        nodesToColor.enqueue(node);
    }

    reverseQueue(nodesToColor);

    emit nodesToColorSignal(nodesToColor);
}

void AbstractGraph::primMST()
{
    QHash<Node*, int> dist;
    QHash<Node*, bool> present;

    auto distanceComparator = [] (std::pair<Node*, int> firstPair, std::pair<Node*, int> secondPair) {
        return firstPair.second > secondPair.second;
    };

    std::priority_queue<std::pair<Node*, int>, std::vector<std::pair<Node*, int>>,
            decltype(distanceComparator)> pq(distanceComparator);

    for(auto const &e : this->getKeys()) {
        dist[e] = INT_MAX;
        present[e] = false;
    }

    for(auto const &e : this->getKeys()) {
        if(!adjList[e].empty()) {
            pq.push(std::make_pair(e, 0));
            dist[e] = 0;
            break;
        }
    }

    while(!pq.empty()) {

        Node *topNode = pq.top().first;
        pq.pop();

        if(!present[topNode]) {

            present[topNode] = true;
            nodesToColor.enqueue(topNode);

            QHash<Node*, Edge*>::const_iterator i;

            for(i = adjList[topNode].constBegin(); i != adjList[topNode].constEnd(); ++i) {
                if(!present[i.key()]) {
                    pq.push(std::make_pair(i.key(), i.value()->getWeight()));
                }
            }
        }
    }

    emit nodesToColorSignal(nodesToColor);
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
    case primsmst:
        this->primMST();
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

void AbstractGraph::reverseQueue(QQueue<Node*> &queue)
{
    QStack<Node*> stack;

    while(!queue.empty()) {
        stack.push(queue.dequeue());
    }

    while(!stack.empty()) {
        queue.enqueue(stack.pop());
    }
}
