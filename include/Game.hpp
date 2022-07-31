#ifndef GAME_HPP
#define GAME_HPP

#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "GridView.hpp"
#include "SceneView.hpp"
#include "Camera.hpp"

const int k_windowWidth{2048};
const int k_windowHeight{1024};
const std::string k_windowTitle{"Raycaster"};
const sf::Color k_bg{sf::Color::Black};

class Game
{
public:
    Game();
    ~Game();

    void Run();

    bool IsDone();

private:
    void ProcessInput();
    void Update();
    void Draw();
    void RestartClock();

    sf::RenderWindow m_window;
    sf::Clock m_clock;
    float m_dt;
    bool m_done;

    Camera m_cam;
    GridView m_gridView;
    SceneView m_sceneView;
};

#endif