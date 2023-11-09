#include "Pathfinding.h"

Pathfinding::Pathfinding() {}

Pathfinding::~Pathfinding() {}

// A* pathfinding algorithm
vector<Node*> Pathfinding::findPath(vector<vector<int>> map, sf::Vector2f start, sf::Vector2f goal) {

    // Init open list with neighbouring nodes and sort on g+h
    priority_queue<Node*, vector<Node*>, CompareNode> openList;

    // Init closed list and set false to all, change to true when already visited
    vector<vector<bool>> closedList(map.size(), vector<bool>(map[0].size(), false));

    // Create start and goal nodes
    Node* startNode = new Node(start.x/40, start.y/40, 0, 0, nullptr);
    Node* goalNode = new Node(goal.x, goal.y, 0, 0, nullptr);
    
    cout << "------------------" << endl;
    cout << startNode->x << " " << startNode->y << endl;
    cout << goalNode->x << " " << goalNode->y << endl;
    cout << "------------------" << endl;
    
    while (!openList.empty()) {
        Node* currentNode = openList.top();
        openList.pop();

        // Check if the goal is reached
        if (currentNode->x == goalNode->x && currentNode->y == goalNode->y) {
            // Reconstruct the path and return it
            vector<Node*> path;
            while (currentNode != nullptr) {
                path.push_back(currentNode);
                currentNode = currentNode->parent;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        //cout << currentNode->x << " " << currentNode->y << endl;
        closedList[currentNode->y][currentNode->x] = true;

        // Define possible neighbor offsets
        int dx[] = { -1, 1, 0, 0 };
        int dy[] = { 0, 0, -1, 1 };

        for (int i = 0; i < 4; i++) {
            int x = currentNode->x + dx[i];
            int y = currentNode->y + dy[i];

            if (x < 0 || y>= map.size() || y < 0 || x >= map[0].size() || map[y][x] == 1 || closedList[y][x])
                continue;

            int g = currentNode->g + 1;
            int h = abs(x - goalNode->x) + abs(y - goalNode->y); // Manhattan distance

            Node* neighbor = new Node(x, y, g, h, currentNode);
            openList.push(neighbor);
        }
    }

    return {}; // No path found
}