#include "Map.h"
#include <fstream>
#include <iostream>

Map::Map()
{
    std::cout << "Map created" << std::endl;
}

Map::~Map()
{
    // Deallocate memory for the Tile objects in tileMap
    for (int i = 0; i < tileMap.size(); i++) {
        for (int j = 0; j < tileMap[i].size(); j++) {
            delete tileMap[i][j];
        }
    }
}

void Map::loadMapFromFile(const std::string &filename)
{
    std::ifstream openfile(filename);
    if (openfile.is_open())
    {
        std::vector<int> row;
        std::string line;
        while (std::getline(openfile, line))
        {
            row.clear();
            for (char c : line)
            {
                int tileType = c -'0';
                row.push_back(tileType);
            }
            this->tilemap.push_back(row);
        }   
    }
}

Map& Map::operator=(const Map& other)
{
    if (this == &other) {
        return *this; // Handle self-assignment
    }

    // Clear the existing map
    for (int i = 0; i < tileMap.size(); i++) {
        for (int j = 0; j < tileMap[i].size(); j++) {
            delete tileMap[i][j];
        }
    }
    tileMap.clear();

    // Copy the tilemap from 'other'
    this->tilemap = other.tilemap;

    // Initialize new tiles based on 'other'
    initTiles();

    return *this;
}

Map::Map(const Map& other)
{
    // Copy the tilemap from 'other'
    this->tilemap = other.tilemap;

    // Initialize new tiles based on 'other'
    initTiles();
}

void Map::initTiles()
{
    std::vector<Tile*> row;
    for (int i = 0; i < tilemap.size(); i++)
    {   
        row.clear();
        for (int j = 0; j < tilemap[i].size(); j++)
        {   
            if (tilemap[i][j] == 2)
            {
                row.push_back(new Tile(tilemap[i][j], j*40, i*40, true));
            } else
            {   
                row.push_back(new Tile(tilemap[i][j], j*40, i*40, false));
            }
        }
        this->tileMap.push_back(row);
    }   
}

std::vector<std::vector<Tile*>> Map::getTiles()
{
    return this->tileMap;
}

std::vector<std::vector<int>> Map::getintMap()
{
    return this->tilemap;
}

void Map::render(sf::RenderTarget* target)
 {
    for (int i = 0; i < tileMap.size(); i++)
    {
        for (int j = 0; j < tileMap[i].size(); j++)
        {
            tileMap[i][j]->render(target);
        }
        
    }
 }