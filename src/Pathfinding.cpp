#include "Pathfinding.h"

Pathfinding::Pathfinding() {}

Pathfinding::~Pathfinding() {}

// A* pathfinding algorithm
vector<Node*>* Pathfinding::findPath(vector<vector<TileType>> map, sf::Vector2f start, sf::Vector2f goal) {

    // Init open list with neighbouring nodes and sort on g+h
    priority_queue<Node*, vector<Node*>, CompareNodeDijkstra> openList;

    // Init closed list and set false to all, change to true when already visited
    vector<vector<bool>> closedList(map.size(), vector<bool>(map[0].size(), false));

    Node* startNode = new Node(start.x/40.f, start.y/40.f, 0, 0, nullptr);
    Node* goalNode = new Node(goal.x, goal.y, 0, 0, nullptr);

    // cout << "-------" << endl;
    // cout << "startnode " << startNode->x << " " << startNode->y << endl;
    // cout << "goalNode " << goalNode->x << " " << goalNode->y << endl;
    // cout << "-------" << endl;

    openList.push(startNode);
    
    while (!openList.empty()) {
        Node* currentNode = openList.top();
        openList.pop();

        //std::cout << "Current Node: (" << currentNode->x << ", " << currentNode->y << ")" << std::endl;

        // Check if the goal is reached
        if (currentNode->x == goalNode->x && currentNode->y == goalNode->y) {
            // Reconstruct the path and return it
            auto path = new vector<Node*>();
            while (currentNode != nullptr) {
                path->push_back(currentNode);
                currentNode = currentNode->parent;
            }
            reverse(path->begin(), path->end());
            return path;
        }

        closedList[currentNode->y][currentNode->x] = true;

        // Define possible neighbor offsets
        int dx[] = { -1, 1, 0, 0 };
        int dy[] = { 0, 0, -1, 1 };

        for (int i = 0; i < 4; i++) {
            int x = currentNode->x + dx[i];
            int y = currentNode->y + dy[i];

            if (x < 0 || y < 0 || x >= map[0].size() || y >= map.size() || map[y][x] == TileType::Wall || closedList[y][x])
                continue;

            int g = currentNode->g + 1;
            // int h = abs(x - goalNode->x) + abs(y - goalNode->y); // Manhattan distance

            Node* neighbor = new Node(x, y, g, 0, currentNode);
            openList.push(neighbor);
            //std::cout << "Added Neighbor: (" << neighbor->x << ", " << neighbor->y << ")" << std::endl;
        }
    }

    // cerr << "NO PATH FOUND" << endl;
    auto path = new vector<Node*>();
    return path; // No path found
}