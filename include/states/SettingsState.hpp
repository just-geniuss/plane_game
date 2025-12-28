#pragma once

#include "states/GameState.hpp"
#include "ui/Button.hpp"
#include <vector>

class SettingsState : public GameState
{
public:
    explicit SettingsState(Game& game);

    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderTarget& target) override;

private:
    void refreshTexts();

    std::vector<Button> buttons;
    sf::Text title;
    sf::Text details;
};
