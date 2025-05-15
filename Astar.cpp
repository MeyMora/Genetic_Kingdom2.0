#include "Node.cpp"
#include <cmath>
#include <algorithm>

Node* getClosest(std::vector<Node*>& openNodes) {
    int closestIndex = 0;
    for (int i = 1; i < openNodes.size(); i++) {
        if (openNodes[i]->getF() < openNodes[closestIndex]->getF()) {
            closestIndex = i;
        }
    }
    Node* closest = openNodes[closestIndex];
    openNodes.erase(openNodes.begin() + closestIndex);
    return closest;
}

bool containsNode(const std::vector<Node*>& nodes, Node* target) {
    for (Node* node : nodes) {
        if (node == target) {
            return true;
        }
    }
    return false;
}

std::vector<Node*> getPath(Node* source, Node* goal) {
    std::vector<Node*> openNodes;
    std::vector<Node*> closedNodes;
    source->setF(0);
    openNodes.push_back(source);
    Node* currentNode ;
    while (!openNodes.empty()) {
        currentNode = getClosest(openNodes);
        std::vector<Node*> neighbors = currentNode->getNeighbors();
        for (Node* adjacent : neighbors) {
            if (adjacent->isFree()) {
                if (!containsNode(closedNodes, adjacent)) {
                    adjacent->setH(abs(adjacent->getX() - goal->getX()) + abs(adjacent->getY() - goal->getY()));
                    int dx = abs(adjacent->getX() - currentNode->getX());
                    int dy = abs(adjacent->getY() - currentNode->getY());
                    int g = (dx == 1 && dy == 1) ? 14 : 10;
                    int f = currentNode->getF() + adjacent->getH() + g;
                    if (f < adjacent->getF()) {
                        adjacent->setG(g);
                        adjacent->setParent(currentNode);
                        adjacent->setF(f);
                        if (!containsNode(openNodes, adjacent)) {
                            openNodes.push_back(adjacent);
                        }
                        if (adjacent == goal) {
                            openNodes.clear();
                        }
                    }
                }
            }
        }
        closedNodes.push_back(currentNode);
    }
    std::vector<Node*> path;
    path.push_back(goal);
    Node* nodePtr = goal->getParent();
    while (nodePtr != nullptr) {
        path.push_back(nodePtr);
        nodePtr = nodePtr->getParent();
    }
    std::reverse(path.begin(), path.end());
    if (path[0] != source) {
        path.clear();
    }
    return path;
}
