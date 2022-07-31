#ifndef GRID_VIEW_HPP
#define GRID_VIEW_HPP

#include <SFML/Graphics.hpp>

#include "View.hpp"
#include "Map.hpp"
#include "Camera.hpp"

class GridView : public View
{
public:
    GridView(sf::Vector2i l_origin, int l_tileSize, int l_borderSize, const Map &l_map, Camera *l_cam);
    ~GridView();

    virtual void Update(float l_dt);

    void ProcessMouseClick(sf::Vector2i l_mousePos);

    void ProcessKeyPress(float l_dt);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    Camera *m_cam;

    Map m_map;
    int m_tileSize;
    int m_borderSize;

    void DrawGrid(sf::RenderTarget& target) const;
    void DrawPlayer(sf::RenderTarget& target) const;
    void DrawRays(sf::RenderTarget& target) const;
};

#endif