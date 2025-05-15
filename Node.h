#ifndef NODE_H
#define NODE_H

#include <vector>
#include <climits>
#include "Casilla.h"

class Node {
    private:
    int G = INT_MAX;
    int H = 0;
    int F = INT_MAX;
    Node* parent = nullptr;
    Casilla* tile;
    std::vector<Node*> neighbors;

    public:
    Node(Casilla* tile);
    int getX();
    int getY();
    bool isFree();
    void setG(int g);
    int getG();
    void setH(int h);
    int getH();
    void setF(int f);
    int getF();
    void setParent(Node* node);
    Node* getParent();
    void addNeighbor(Node* node);
    std::vector<Node*> getNeighbors();
};

#endif