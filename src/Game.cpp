#include "Game.hpp"

Game::Game() :
    m_window{{k_windowWidth, k_windowHeight}, k_windowTitle}, m_done{false},
    m_gridView{{0,0}, 64, 2, Map(16, 16), &m_cam},
    m_sceneView{{1024, 0}, {1024, 1024}, &m_cam}
{
    m_window.setFramerateLimit(60);
    RestartClock();
}

Game::~Game()
{

}

void Game::Run()
{
    ProcessInput();
    Update();
    Draw();
    RestartClock();
}

bool Game::IsDone()
{
    return m_done;
}

void Game::ProcessInput()
{
    sf::Event ev;
    while (m_window.pollEvent(ev))
    {
        switch (ev.type)
        {
        case (sf::Event::Closed):
            m_done = true;
            break;
        case (sf::Event::MouseButtonPressed):
            m_gridView.ProcessMouseClick(sf::Mouse::getPosition(m_window));
            break;
        default:
            break;
        }
    }
    m_gridView.ProcessKeyPress(m_dt);
}

void Game::Update()
{
    m_gridView.Update(m_dt);
}

void Game::Draw()
{
    m_window.clear(k_bg);

    m_window.draw(m_gridView);
    m_window.draw(m_sceneView);

    m_window.display();
}

void Game::RestartClock()
{
    m_dt = m_clock.restart().asSeconds();
}