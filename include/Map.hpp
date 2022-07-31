#ifndef MAP_HPP
#define MAP_HPP

#include <vector>

#include <SFML/Graphics.hpp>

#include "Tile.hpp"

using MapData = std::vector<Tile>;

class Map
{
public:
    Map(int l_rows, int l_cols);
    Map(sf::Image l_bitmap);
    ~Map();

    void IncrementTileType(int row, int col);

    int GetNumRows() const;
    int GetNumCols() const;
    Tile GetTile(int x, int y) const;
    bool WithinBounds(float x, float y) const;

private:
    MapData m_grid;
    int m_rows;
    int m_cols;

    int GetTileIndex(int x, int y) const;
};

#endif