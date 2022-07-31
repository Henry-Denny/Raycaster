#include "Camera.hpp"

Camera::Camera(sf::Vector2f l_pos, int l_numRays) :
    m_gridPos{l_pos}, m_bearing{PI}, m_movSpeed{3}, m_rotSpeed(PI),
    m_fov{PI / 3.0f}, m_rayLength{10.0f}, m_numRays{l_numRays}, m_rayData(l_numRays)
{

}

Camera::~Camera()
{

}

void Camera::Rotate(bool clockwise, float dt)
{
    m_bearing += m_rotSpeed * dt * (clockwise ? 1 : -1);
    if (m_bearing >= TWO_PI) m_bearing -= TWO_PI;
    else if (m_bearing <= 0.0f) m_bearing += TWO_PI;
}

void Camera::Move(bool forwards, float dt)
{
    float distance = m_movSpeed * dt * (forwards ? 1 : -1);
    m_gridPos += GetRayDir(m_bearing, distance);
}

void Camera::CastRays(const Map &l_map)
{
    for (int i = 0; i < m_numRays; ++i)
    {
        float angle = -(m_fov / 2.0f) + m_fov * (i / float(m_numRays - 1));
        Ray ray;
        CastRay(ray, l_map, angle);
        m_rayData.at(i) = ray;
    }
}

void Camera::CastRay(Ray &ray, const Map &l_map, float angle)
{
    sf::Vector2f rayStart{m_gridPos};
    sf::Vector2f rayDir{GetRayDir(m_bearing + angle)};
    sf::Vector2f rayUnitStepSize
    {
        std::sqrt(1 + (rayDir.y / rayDir.x) * (rayDir.y / rayDir.x)),
        std::sqrt(1 + (rayDir.x / rayDir.y) * (rayDir.x / rayDir.y))
    };

    sf::Vector2i mapCheck{sf::Vector2i(rayStart)};
    sf::Vector2f rayLength{};

    sf::Vector2i step{};

    if (rayDir.x < 0)
    {
        step.x = -1;
        rayLength.x = (rayStart.x - float(mapCheck.x)) * rayUnitStepSize.x;
    }
    else
    {
        step.x = 1;
        rayLength.x = (float(mapCheck.x + 1) - rayStart.x) * rayUnitStepSize.x;
    }
    if (rayDir.y < 0)
    {
        step.y = -1;
        rayLength.y = (rayStart.y - float(mapCheck.y)) * rayUnitStepSize.y;
    }
    else
    {
        step.y = 1;
        rayLength.y = (float(mapCheck.y + 1) - rayStart.y) * rayUnitStepSize.y;
    }

    bool tileFound{false};
    float distance{0.0f};
    while (!tileFound && distance < m_rayLength)
    {
        if (rayLength.x < rayLength.y)
        {
            mapCheck.x += step.x;
            distance = rayLength.x;
            rayLength.x += rayUnitStepSize.x;
            ray.hit = WallType::Vertical;
        }
        else
        {
            mapCheck.y += step.y;
            distance = rayLength.y;
            rayLength.y += rayUnitStepSize.y;
            ray.hit = WallType::Horizontal;
        }

        if (l_map.WithinBounds(mapCheck.x, mapCheck.y))
        {
            if (l_map.GetTile(mapCheck.x, mapCheck.y) != Tile::None)
            {
                tileFound = true;
            }
        }
    }

    if (!tileFound) ray.hit = WallType::None;
    ray.rayEnd = rayStart + (rayDir * distance);
    ray.rayLength = distance * std::cos(angle);
}

void Camera::IncrementFov(float amount)
{
    m_fov += amount;
}

float Camera::GetBearing() const
{
    return m_bearing;
}

sf::Vector2f Camera::GetGridPos() const
{
    return m_gridPos;
}

int Camera::GetNumRays() const
{
    return m_numRays;
}

bool Camera::Intersects(int rayIndex) const
{
    assert(rayIndex >= 0 && rayIndex < m_numRays);
    return !(m_rayData.at(rayIndex).hit == WallType::None);
}

WallType Camera::GetHitID(int rayIndex) const
{
    assert(rayIndex >= 0 && rayIndex < m_numRays);
    return m_rayData.at(rayIndex).hit;
}

sf::Vector2f Camera::GetRayEnd(int rayIndex) const
{
    assert(rayIndex >= 0 && rayIndex < m_numRays);
    return m_rayData.at(rayIndex).rayEnd;
}

float Camera::GetRayLength(int rayIndex) const
{
    assert(rayIndex >= 0 && rayIndex < m_numRays);
    return m_rayData.at(rayIndex).rayLength;
}