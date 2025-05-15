#include "Node.h"



Node::Node(Casilla* tile) {
    this->tile = tile;
}

int Node::getX() {
    return this->tile->x;
}

int Node::getY() {
    return this->tile->y;
}

void Node::setG(int g) {
    this->G = g;
}

int Node::getG() {
    return this->G;
}

void Node::setH(int h) {
    this->H = h;
}

int Node::getH() {
    return this->H;
}

void Node::setF(int f) {
    this->F = f;
}

int Node::getF() {
    return this->F;
}

void Node::setParent(Node* node) {
    this->parent = node;
}
Node* Node::getParent() {
    return this->parent;
}

void Node::addNeighbor(Node* node) {
    this->neighbors.push_back(node);
}

std::vector<Node*> Node::getNeighbors() {
    return this->neighbors;
}

bool Node::isFree() {
    return !this->tile->isBlocked();
}