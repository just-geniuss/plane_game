#pragma once

#include "states/GameState.hpp"
#include "systems/HighScoreSystem.hpp"
#include "ui/Button.hpp"
#include <optional>

class HighScoreState : public GameState
{
public:
    explicit HighScoreState(Game& game);

    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderTarget& target) override;

private:
    HighScoreSystem highScores;
    Button backButton;
#if SFML_VERSION_MAJOR >= 3
    std::optional<sf::Text> title;
#else
    sf::Text title;
#endif
    std::vector<sf::Text> rows;
};
