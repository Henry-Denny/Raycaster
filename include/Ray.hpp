#ifndef RAY_HPP
#define RAY_HPP

#include <SFML/Graphics.hpp>

#include "WallType.hpp"

struct Ray
{
    WallType hit;
    sf::Vector2f rayEnd;
    float rayLength;
};

#endif