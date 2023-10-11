#pragma once

#include <vector>

#include "Tile.h"
#include "Pellet.h"


#include <SFML/Graphics.hpp>

class Map 
{
    private:
        std::vector<std::vector<int>> tilemap;
        std::vector<std::vector<Tile>> tileMap;

    public:
        void initTiles();
        void loadMapFromFile(const std::string &filename = "../util/map_debug.txt");
        std::vector<std::vector<Tile>> getTiles();
        void render(sf::RenderTarget* target);

};