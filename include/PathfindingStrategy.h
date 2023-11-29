// PathfindingStrategy.h
#pragma once

#include <vector>

class PathfindingStrategy {
public:
    virtual ~PathfindingStrategy() {}
    virtual int calculateH(int x, int y, int goalX, int goalY) const = 0;
};

class DijkstraStrategy : public PathfindingStrategy {
public:
    virtual int calculateH(int x, int y, int goalX, int goalY) const override {
        // Dijkstra's algorithm has no heuristic
        return 0;
    }
};

class AStarStrategy : public PathfindingStrategy {
public:
    virtual int calculateH(int x, int y, int goalX, int goalY) const override {
        // A* algorithm heuristic (Manhattan distance)
        return abs(x - goalX) + abs(y - goalY);
    }
};