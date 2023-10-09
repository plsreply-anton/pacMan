#include "../include/Map.h"
#include <fstream>
#include <iostream>

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

void Map::initTiles()
{
    std::vector<Tile> row;
    for (int i = 0; i < tilemap.size(); i++)
    {   
        row.clear();
        for (int j = 0; j < tilemap[i].size(); j++)
        {   
            if (tilemap[i][j] == 2)
            {
                row.push_back(Tile(tilemap[i][j], j*10, i*10, true));
            } else
            {   
                row.push_back(Tile(tilemap[i][j], j*10, i*10, false));
            }
        }
        this->tileMap.push_back(row);
    }   
}

std::vector<std::vector<Tile>> Map::getTiles()
{
    return this->tileMap;
}

void Map::render(sf::RenderTarget* target)
 {
    for (int i = 0; i < tileMap.size(); i++)
    {
        for (int j = 0; j < tileMap[i].size(); j++)
        {
            tileMap[i][j].render(target);
        }
        
    }
 }