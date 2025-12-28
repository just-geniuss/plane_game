#pragma once

#include "states/GameState.hpp"
#include "ui/Button.hpp"
#include <vector>
#include <optional>

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
#if SFML_VERSION_MAJOR >= 3
    std::optional<sf::Text> title;
    std::optional<sf::Text> details;
#else
    sf::Text title;
    sf::Text details;
#endif
};
