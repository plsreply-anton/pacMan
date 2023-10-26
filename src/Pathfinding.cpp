#include "Pathfinding.h"

Pathfinding::Pathfinding() {}

Pathfinding::~Pathfinding() {}

// A* pathfinding algorithm
vector<Node*> Pathfinding::findPath(vector<vector<int>> map, sf::Vector2f start, sf::Vector2f goal) {

    // Initialize open and closed lists
    priority_queue<Node*, vector<Node*>, CompareNode> openList;
    vector<vector<bool>> closedList(map.size(), vector<bool>(map[0].size(), false));

    // Create start and goal nodes
    Node* startNode = new Node(start.x/40, start.y/40, 0, 0, nullptr);
    Node* goalNode = new Node(goal.x, goal.y, 0, 0, nullptr);

    if (abs(start.x/40 - goal.x) < 2 && abs(start.y/40-goal.y) < 2 )
    {
        return {};
    }
    
    
    cout << "------------------" << endl;
    cout << startNode->x << " " << startNode->y << endl;
    cout << startNode->x << " " << startNode->y << endl;
    cout << "------------------" << endl;
    
    openList.push(startNode);

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

        cout << currentNode->x << " " << currentNode->y << endl;
        closedList[currentNode->x][currentNode->y] = true;

        // Define possible neighbor offsets (assuming 4-directional movement)
        int dx[] = { -1, 1, 0, 0 };
        int dy[] = { 0, 0, -1, 1 };

        for (int i = 0; i < 4; i++) {
            int x = currentNode->x + dx[i];
            int y = currentNode->y + dy[i];

            if (x < 0 || x >= map.size() || y < 0 || y >= map[0].size() || map[x][y] == 1 || closedList[x][y]) {
                continue;
            }

            int g = currentNode->g + 1;
            int h = abs(x - goalNode->x) + abs(y - goalNode->y); // Manhattan distance

            Node* neighbor = new Node(x, y, g, h, currentNode);
            openList.push(neighbor);
        }
    }

    return {}; // No path found
}