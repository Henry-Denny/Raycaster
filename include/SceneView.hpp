#ifndef SCENE_VIEW_HPP
#define SCENE_VIEW_HPP

#include "View.hpp"
#include "Camera.hpp"
#include "WallType.hpp"

class SceneView : public View
{
public:
    SceneView(sf::Vector2i l_origin, sf::Vector2i l_size, const Camera *l_cam);
    ~SceneView();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    virtual void Update(float l_dt);

private:
    const Camera *m_cam;
    float cubeHeight;
};

#endif