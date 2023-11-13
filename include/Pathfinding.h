#pragma once

#include <vector>
#include <stack>
#include <fstream>
#include <sstream>
#include <iostream>

#include <queue>
#include <limits>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Map.h"

using namespace std;

// Define a structure for a map node
struct Node {
    int x, y;      // Coordinates of the node
    int g, h;      // Cost from the start (g) and heuristic to the goal (h)
    Node* parent;  // Parent node

    Node(int x, int y, int g, int h, Node* parent) : x(x), y(y), g(g), h(h), parent(parent) {}
};

// Define a custom comparator for the priority queue
struct CompareNode {
    bool operator()(Node* a, Node* b) {
        return (a->g + a->h) < (b->g + b->h);
    }
};

struct CompareNodeDijkstra {
    bool operator()(Node* const& a, Node* const& b) {
        return a->g < b->g; // Min-heap: smaller g values have higher priority
    }
};

class Pathfinding {

public:
    Pathfinding();
    ~Pathfinding();
    vector<Node*>* findPath(vector<vector<TileType>> map, sf::Vector2f start, sf::Vector2f goal);
};


