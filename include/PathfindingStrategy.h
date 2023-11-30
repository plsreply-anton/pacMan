#pragma once

#include <vector>

class PathfindingStrategy {
public:
    virtual ~PathfindingStrategy() {}
    virtual int calculateH(int x, int y, int goalX, int goalY) const = 0;
};

class DijkstraStrategy : public PathfindingStrategy {
public:
    int calculateH(int x, int y, int goalX, int goalY) const override;
};

class AStarStrategy : public PathfindingStrategy {
public:
    int calculateH(int x, int y, int goalX, int goalY) const override;
};