#include "SceneView.hpp"

SceneView::SceneView(sf::Vector2i l_origin, sf::Vector2i l_size, const Camera *l_cam) :
    m_cam{l_cam}, cubeHeight{40.0f}, View(l_origin, l_size)
{

}

SceneView::~SceneView()
{

}

void SceneView::Update(float l_dt)
{

}

void SceneView::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    int numSegments{m_cam->GetNumRays()};
    float segmentWidth = {float(m_size.x) / numSegments};
    sf::RectangleShape segment{{segmentWidth, 1.0f}};
    sf::FloatRect rect = segment.getLocalBounds();
    segment.setOrigin(rect.left, rect.top + (rect.height / 2.0f));
    segment.setPosition(float(m_origin.x), float(m_origin.y) + (m_size.y / 2.0f));
    segment.setFillColor(sf::Color::Red);
    for (int i = 0; i < numSegments; ++i)
    {
        if (m_cam->Intersects(i))
        {
            float dist = m_cam->GetRayLength(i);
            float segmentHeight {m_size.y / dist};
            segment.setScale({1.0f, segmentHeight});
            WallType wallType{m_cam->GetHitID(i)};
            float intensity = (wallType == WallType::Vertical) ? 240.0f : 160.0f;
            intensity /= dist;
            if (intensity >= 255.0f) intensity = 255.0f;
            sf::Color wallCol = ((wallType == WallType::Vertical) ? sf::Color(int(intensity),0,0) : sf::Color(int(intensity),0,0));
            segment.setFillColor(wallCol);
            target.draw(segment);
        }
        
        segment.move({segmentWidth, 0.0f});
    }
}