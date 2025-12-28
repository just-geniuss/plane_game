#pragma once

#include <memory>
#include <vector>
#include <functional>

#include "states/GameState.hpp"

class StateStack
{
public:
    explicit StateStack(Game& game);

    template <typename State, typename... Args>
    void push(Args&&... args)
    {
        states.emplace_back(std::make_unique<State>(game, std::forward<Args>(args)...));
    }

    void pop();
    void clear();

    void handleEvent(const sf::Event& event);
    void update(float dt);
    void draw(sf::RenderTarget& target);

    bool empty() const { return states.empty(); }

private:
    Game& game;
    std::vector<std::unique_ptr<GameState>> states;
};
