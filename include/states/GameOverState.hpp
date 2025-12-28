#pragma once

#include "states/GameState.hpp"
#include "systems/HighScoreSystem.hpp"
#include "ui/Button.hpp"
#include <optional>

class GameOverState : public GameState
{
public:
    GameOverState(Game& game, int finalScore, HighScoreSystem scores);

    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderTarget& target) override;

private:
    void refreshTable();

    int score{0};
    HighScoreSystem highScores;
#if SFML_VERSION_MAJOR >= 3
    std::optional<sf::Text> title;
    std::optional<sf::Text> inputLabel;
    std::optional<sf::Text> nameText;
#else
    sf::Text title;
    sf::Text inputLabel;
    sf::Text nameText;
#endif
    std::vector<sf::Text> rows;
    Button backButton;
    std::string nameBuffer{"AAA"};
    bool submitted{false};
};
