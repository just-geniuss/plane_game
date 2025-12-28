#pragma once

#include "states/GameState.hpp"
#include "systems/HighScoreSystem.hpp"
#include "ui/Button.hpp"

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
    sf::Text title;
    std::vector<sf::Text> rows;
};
