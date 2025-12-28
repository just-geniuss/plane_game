#include "states/HighScoreState.hpp"

#include "core/Game.hpp"

namespace
{
const std::string HIGHSCORE_PATH = "assets/config/highscores.txt";
}

HighScoreState::HighScoreState(Game& g) : GameState(g)
{
    const sf::Font* font = nullptr;
    if (g.fonts().contains("default"))
        font = &g.fonts().get("default");

    highScores.load(HIGHSCORE_PATH);

    if (font)
        title.setFont(*font);
    title.setString("High Scores");
    title.setCharacterSize(32);
    title.setPosition({40.f, 30.f});

    float y = 90.f;
    for (const auto& entry : highScores.entries())
    {
        sf::Text text;
        if (font)
            text.setFont(*font);
        text.setCharacterSize(20);
        text.setPosition({60.f, y});
        text.setString(entry.name + " - " + std::to_string(entry.score));
        rows.push_back(text);
        y += 32.f;
    }

    backButton.setPosition({g.getWindow().getSize().x - 120.f, g.getWindow().getSize().y - 60.f});
    backButton.setSize({180.f, 44.f});
    backButton.setText("Back", font, 22);
    backButton.setCallback([this]() { game.stateStack().pop(); });
}

void HighScoreState::handleEvent(const sf::Event& event)
{
    backButton.handleEvent(event, game.getWindow());
}

void HighScoreState::update(float)
{
}

void HighScoreState::draw(sf::RenderTarget& target)
{
    if (title.getFont())
        target.draw(title);
    for (auto& r : rows)
    {
        if (r.getFont())
            target.draw(r);
    }
    backButton.draw(target);
}
