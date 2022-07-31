#include "Map.hpp"

Map::Map(int l_rows, int l_cols) :
    m_rows{l_rows}, m_cols{l_cols}, m_grid(l_rows * l_cols, Tile::None)
{

}

Map::Map(sf::Image l_bitmap)
{

}

Map::~Map()
{

}

void Map::IncrementTileType(int row, int col)
{
    int index = GetTileIndex(row, col);
    Tile &tile{m_grid[index]};

    int nextTileIndex = (int)tile + 1;
    if (nextTileIndex >= (int)Tile::Count) nextTileIndex = 0;

    tile = (Tile)nextTileIndex;
}


int Map::GetNumRows() const
{
    return m_rows;
}

int Map::GetNumCols() const
{
    return m_cols;
}

Tile Map::GetTile(int x, int y) const
{
    return m_grid[(y * m_cols) + x];
}

bool Map::WithinBounds(float x, float y) const
{
    return (x >= 0.0f && x <= float(m_cols) && y >= 0.0f && y < float(m_rows));
}

int Map::GetTileIndex(int x, int y) const
{
    return (y * m_cols) + x;
}