#pragma once

#include <vector>

#include "Tile.h"
#include "Pellet.h"

enum TileType
{
    Space,
    Wall,
    Pellet,
    Energizer
};

class Map 
{
    private:
        std::vector<std::vector<TileType>> tilemap;
        std::vector<std::vector<Tile *>> tileMap;
        int totalPellets = 0;

    public:
        //Constructor and destructor
        Map();
        ~Map();

        //Assignment operator
        Map& operator=(const Map& other);

        //Copy Constructor
        Map(const Map& other);

        //Initializer
        void initTiles();
        void loadMapFromFile(const std::string &filename = "../util/map.txt");

        //Getters
        std::vector<std::vector<TileType>> getintMap() const;
        int getTotalPellets() const;
        std::vector<std::vector<Tile*>> getTiles() const;

        void render(sf::RenderTarget* target);
};