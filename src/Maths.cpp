#include "Maths.hpp"

sf::Vector2f GetRayDir(float bearing, float magnitude)
{
    sf::Vector2f rayDir{};

    if (bearing >= 0.0f && bearing < PI / 2.0f)
    {
        rayDir.x = magnitude * std::sin(bearing);
        rayDir.y = -magnitude * std::cos(bearing);
    }
    else if (bearing >= PI / 2.0f && bearing < PI)
    {
        rayDir.x = magnitude * std::sin(PI - bearing);
        rayDir.y = magnitude * std::cos(PI - bearing);
    }
    else if (bearing >= PI && bearing < 3 * (PI / 2.0f))
    {
        rayDir.x = -magnitude * std::sin(bearing - PI);
        rayDir.y = magnitude * std::cos(bearing - PI);
    }
    else
    {
        rayDir.x = -magnitude * std::sin(TWO_PI - bearing);
        rayDir.y = -magnitude * std::cos(TWO_PI - bearing);
    }
    
    return rayDir;
}