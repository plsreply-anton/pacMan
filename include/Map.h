#pragma once

#include <vector>

#include "Tile.h"
#include "Pellet.h"

enum TileType
{
    Space,
    Wall
};

class Map 
{
    private:
        std::vector<std::vector<TileType>> tilemap;
        std::vector<std::vector<Tile *>> tileMap;

    public:
        Map();
        ~Map();
        Map& operator=(const Map& other);
        Map(const Map& other);
        std::vector<std::vector<TileType>> getintMap();
        
        void initTiles();
        void loadMapFromFile(const std::string &filename = "../util/map.txt");
        std::vector<std::vector<Tile*>> getTiles();
        void render(sf::RenderTarget* target);

};