#pragma once

#include "states/GameState.hpp"
#include "ui/Button.hpp"
#include <vector>

class MainMenuState : public GameState
{
public:
    explicit MainMenuState(Game& game);

    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderTarget& target) override;

private:
    std::vector<Button> buttons;
};
