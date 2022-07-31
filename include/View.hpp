#ifndef VIEW_HPP
#define VIEW_HPP

#include <SFML/Graphics.hpp>

class View : public sf::Drawable
{
public:
    View(sf::Vector2i l_origin, sf::Vector2i l_size, sf::Color l_bgColour=sf::Color::Black);
    ~View();

    virtual void Update(float l_dt) = 0;

    bool WithinBounds(sf::Vector2f l_pos) const;

protected:
    sf::Vector2i m_origin;
    sf::Vector2i m_size;
    sf::Color m_bgColour;
};

#endif