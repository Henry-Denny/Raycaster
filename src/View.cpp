#include "View.hpp"

View::View(sf::Vector2i l_origin, sf::Vector2i l_size, sf::Color l_bgColour) : m_origin{l_origin}, m_size{l_size}, m_bgColour{l_bgColour}
{
    
}

View::~View()
{

}

bool View::WithinBounds(sf::Vector2f l_pos) const
{
    return  l_pos.x > m_origin.x &&
            l_pos.x < (m_origin.x + m_size.x) &&
            l_pos.y > m_origin.y &&
            l_pos.y < (m_origin.y + m_size.y);
}