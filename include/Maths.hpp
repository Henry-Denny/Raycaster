#ifndef MATHS_HPP
#define MATHS_HPP

#include <cmath>

#include <SFML/System/Vector2.hpp>

#define PI 3.1415926535
#define TWO_PI (2 * PI)

sf::Vector2f GetRayDir(float bearing, float magnitude=1.0f);

#endif