#include "GridView.hpp"

GridView::GridView(sf::Vector2i l_origin, int l_tileSize, int l_borderSize, const Map &l_map, Camera *l_cam) :
    m_map{l_map}, m_cam{l_cam}, m_tileSize{l_tileSize}, m_borderSize{l_borderSize},
    View(l_origin, sf::Vector2i(l_map.GetNumCols(), l_map.GetNumRows()) * l_tileSize, sf::Color({17, 17, 200}))
{

}

GridView::~GridView()
{

}

void GridView::Update(float l_dt)
{
    m_cam->CastRays(m_map);
}

void GridView::ProcessMouseClick(sf::Vector2i l_mousePos)
{
    if (!WithinBounds((sf::Vector2f)l_mousePos)) return;
    sf::Vector2u gridPos{sf::Vector2u((l_mousePos - m_origin) / m_tileSize)};
    m_map.IncrementTileType(gridPos.x, gridPos.y);
}

void GridView::ProcessKeyPress(float l_dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) m_cam->Move(true, l_dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) m_cam->Move(false, l_dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) m_cam->Rotate(false, l_dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) m_cam->Rotate(true, l_dt);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) m_cam->IncrementFov(1.0f * l_dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) m_cam->IncrementFov(-1.0f * l_dt);
}

void GridView::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    DrawGrid(target);
    DrawPlayer(target);
    DrawRays(target);
}

void GridView::DrawGrid(sf::RenderTarget& target) const
{
    sf::RectangleShape m_tile{{float(m_tileSize - m_borderSize), float(m_tileSize - m_borderSize)}};
    m_tile.setPosition(m_origin.x, m_origin.y);

    for (int y = 0; y < m_map.GetNumRows(); ++y)
    {
        for (int x = 0; x < m_map.GetNumCols(); ++x)
        {
            m_tile.setPosition(m_origin.x + x * m_tileSize, m_origin.y + y * m_tileSize);
            switch (m_map.GetTile(x, y))
            {
            case (Tile::None):
                m_tile.setFillColor({17, 17, 17});
                break;

            case (Tile::Red):
                m_tile.setFillColor(sf::Color::Red);
            
            default:
                break;
            }
            target.draw(m_tile);
        }
    }
}

void GridView::DrawPlayer(sf::RenderTarget& target) const
{
    sf::Vector2f playerPos{sf::Vector2f(m_origin) + m_cam->GetGridPos() * float(m_tileSize)};
    sf::RectangleShape indicator{{5, 80}};
    sf::FloatRect indicatorRect{indicator.getLocalBounds()};
    indicator.setOrigin(indicatorRect.left + (indicatorRect.width / 2.0f), indicatorRect.top + indicatorRect.height);
    indicator.setFillColor(sf::Color::Magenta);
    indicator.setPosition(playerPos);
    indicator.setRotation((m_cam->GetBearing() / PI) * 180.0f);
    target.draw(indicator);

    sf::CircleShape shape{16};
    sf::FloatRect shapeRect{shape.getLocalBounds()};
    shape.setOrigin(shapeRect.left + (shapeRect.width / 2.0f), shapeRect.top + (shapeRect.height / 2.0f));
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(playerPos);
    target.draw(shape);
}

void GridView::DrawRays(sf::RenderTarget& target) const
{
    sf::Vector2f playerPos{sf::Vector2f(m_origin) + m_cam->GetGridPos() * float(m_tileSize)};

    for (int i = 0; i < m_cam->GetNumRays(); ++i)
    {
        sf::Vector2f scaledIntersection{sf::Vector2f(m_origin) + m_cam->GetRayEnd(i) * float(m_tileSize)};
        sf::Color col{sf::Color::White};
        if (m_cam->GetHitID(i) == WallType::Horizontal) col = sf::Color::Cyan;
        else if (m_cam->GetHitID(i) == WallType::Vertical) col = sf::Color::Yellow;
        sf::Vertex ray[] =
        {
            {playerPos, col},
            {scaledIntersection, col}
        };
        target.draw(ray, 2, sf::Lines);

        if (!m_cam->Intersects(i)) continue;

        sf::CircleShape shape{8};
        sf::FloatRect shapeRect{shape.getLocalBounds()};
        shape.setOrigin(shapeRect.left + (shapeRect.width / 2.0f), shapeRect.top + (shapeRect.height / 2.0f));
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineColor(sf::Color::Green);
        shape.setOutlineThickness(2.0f);
        shape.setPosition(scaledIntersection);
        target.draw(shape);
    }
}