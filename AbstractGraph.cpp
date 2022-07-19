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
        emit graphColoringSignal(nodesToColor);
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
            emit graphColoringSignal(nodesToColor);
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
    auto distanceComparator = [] (std::pair<Node*, Edge*> firstPair, std::pair<Node*, Edge*> secondPair) {
        return firstPair.second > secondPair.second;
    };

    std::priority_queue<std::pair<Node*, Edge*>, std::vector<std::pair<Node*, Edge*>>,
            decltype(distanceComparator)> pq(distanceComparator);

    pq.push(std::make_pair(startingNode, new Edge));


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
                pq.push(std::make_pair(i.key(), i.value()));
                parent[i.key()] = topNode;
            }
        }
    }

    //finding shortest path from startingNode to soughtNode
    Node *node = soughtNode;
    nodesToColor.enqueue(node);

    while(node != startingNode) {
        edgesToColor.enqueue(adjList[node][parent[node]]);
        node = parent[node];
        nodesToColor.enqueue(node);
    }

    reverseQueue(nodesToColor);
    reverseQueue(edgesToColor);

    emit graphColoringSignal(nodesToColor, edgesToColor);
}

void AbstractGraph::primMST()
{
    QHash<Node*, bool> present;

    auto distanceComparator = [] (std::pair<Node*, Edge*> firstPair, std::pair<Node*, Edge*> secondPair) {
        return firstPair.second->getWeight() > secondPair.second->getWeight();
    };

    std::priority_queue<std::pair<Node*, Edge*>, std::vector<std::pair<Node*, Edge*>>,
            decltype(distanceComparator)> pq(distanceComparator);

    for(auto const &e : this->getKeys()) {
        present[e] = false;
    }

    for(auto const &e : this->getKeys()) {
        if(!adjList[e].empty()) {
            pq.push(std::make_pair(e, new Edge));
            break;
        }
    }

    while(!pq.empty()) {

        Node *topNode = pq.top().first;
        Edge *topEdge = pq.top().second;

        pq.pop();

        if(!present[topNode]) {

            present[topNode] = true;
            nodesToColor.enqueue(topNode);
            edgesToColor.enqueue(topEdge);

            QHash<Node*, Edge*>::const_iterator i;

            for(i = adjList[topNode].constBegin(); i != adjList[topNode].constEnd(); ++i) {
                if(!present[i.key()]) {
                    pq.push(std::make_pair(i.key(), i.value()));
                }
            }
        }
    }

    //first added edge is a dummy edge thus getting rid of it
    edgesToColor.pop_front();

    emit graphColoringSignal(nodesToColor, edgesToColor);
}

void AbstractGraph::hamiltonianCycle()
{
    QHash<Node*, Node*> parent;

    for(auto const &e : this->getKeys()) {
        visited[e] = true;
        hamiltonianBacktrack(parent, e, e, 1);
        break;
    }
}

void AbstractGraph::hamiltonianBacktrack(QHash<Node*, Node*> &parent, Node *firstNode, Node *node, int visitedNumber)
{
    QHash<Node*, Edge*>::const_iterator i;

    for(i = adjList[node].constBegin(); i != adjList[node].constEnd(); ++i) {
        if(!nodesToColor.empty()) {
            break;
        }
        else if(!visited[i.key()]) {
            visited[i.key()] = true;
            parent[node] = i.key();
            hamiltonianBacktrack(parent, firstNode, i.key(), visitedNumber + 1);
            visited[i.key()] = false;
        }
        else if(firstNode == i.key() && this->getKeys().size() == visitedNumber) {
            parent[node] = i.key();

            node = parent[node];
            edgesToColor.enqueue(adjList[node][parent[node]]);
            nodesToColor.enqueue(node);
            node = parent[node];

            while(node != firstNode) {
                edgesToColor.enqueue(adjList[node][parent[node]]);
                nodesToColor.enqueue(node);
                node = parent[node];
            }

            emit graphColoringSignal(nodesToColor, edgesToColor);
            return;
        }
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
    case primsmst:
        this->primMST();
        break;
    default:
        qDebug() << "unknown algorithm type";
        break;
    }

    resetAlgorithm();
}

void AbstractGraph::getAlgorithmType(algorithmType aType)
{ 
    this->aType = aType;


    // if no nodes are needed for an algorithm running algorithm can be handles right after clicking start algorithm button
    switch(aType) {
    case primsmst:
        this->primMST();
        break;
    case hamcycle:
        this->hamiltonianCycle();
        break;
    default:
        break;
    }

    resetAlgorithm();
}

void AbstractGraph::resetAlgorithm()
{
    algorithmStartingNode = nullptr;
    algorithmEndingNode = nullptr;

    for(auto const &e : getKeys()) {
        visited[e] = false;
    }

    nodesToColor.clear();
    edgesToColor.clear();
}

template <typename T>
void AbstractGraph::reverseQueue(QQueue<T*> &queue)
{
    QStack<T*> stack;

    while(!queue.empty()) {
        stack.push(queue.dequeue());
    }

    while(!stack.empty()) {
        queue.enqueue(stack.pop());
    }
}
