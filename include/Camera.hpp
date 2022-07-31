#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <cmath>
#include <cassert>

#include <SFML/Graphics.hpp>

#include "Maths.hpp"
#include "Map.hpp"
#include "Tile.hpp"
#include "Ray.hpp"
#include "WallType.hpp"

using RayArray = std::vector<Ray>;

class Camera
{
public:
    Camera(sf::Vector2f l_pos={0,0}, int l_numRays=120);
    ~Camera();

    void Rotate(bool clockwise, float dt);
    void Move(bool forwards, float dt);

    void CastRays(const Map &l_map);
    void CastRay(Ray &ray, const Map &l_map, float angle);

    void IncrementFov(float amount);

    float GetBearing() const;
    sf::Vector2f GetGridPos() const;
    int GetNumRays() const;

    bool Intersects(int rayIndex) const;
    WallType GetHitID(int rayIndex) const;
    sf::Vector2f GetRayEnd(int rayIndex) const;
    float GetRayLength(int rayIndex) const;

private:
    RayArray m_rayData;
    sf::Vector2f m_gridPos;
    float m_bearing;
    float m_movSpeed;   // Tiles per second
    float m_rotSpeed;   // Radians per second

    float m_fov;
    float m_rayLength;
    int m_numRays;
};

#endif