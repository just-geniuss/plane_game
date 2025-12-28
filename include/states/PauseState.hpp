#pragma once

#include "states/GameState.hpp"
#include "ui/Button.hpp"
#include <vector>
#include <optional>

class PauseState : public GameState
{
public:
    explicit PauseState(Game& game);

    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderTarget& target) override;

private:
    std::vector<Button> buttons;
#if SFML_VERSION_MAJOR >= 3
    std::optional<sf::Text> title;
#else
    sf::Text title;
#endif
};
