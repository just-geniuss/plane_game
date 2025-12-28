#pragma once

#include <SFML/Graphics.hpp>

class Game;

class GameState
{
public:
    explicit GameState(Game& game) : game(game) {}
    virtual ~GameState() = default;

    virtual void handleEvent(const sf::Event& event) = 0;
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderTarget& target) = 0;

protected:
    Game& game;
};
