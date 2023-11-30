#include "PathfindingStrategy.h"

int DijkstraStrategy::calculateH(int x, int y, int goalX, int goalY) const {
    // Dijkstra's algorithm has no heuristic
    return 0;
}

int AStarStrategy::calculateH(int x, int y, int goalX, int goalY) const {
    // A* algorithm heuristic (Manhattan distance)
    return abs(x - goalX) + abs(y - goalY);
}