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

#if SFML_VERSION_MAJOR >= 3
    if (font)
    {
        title.emplace(*font, "High Scores", 32);
        title->setPosition({40.f, 30.f});
    }
#else
    if (font)
        title.setFont(*font);
    title.setString("High Scores");
    title.setCharacterSize(32);
    title.setPosition({40.f, 30.f});
#endif

    float y = 90.f;
    for (const auto& entry : highScores.entries())
    {
#if SFML_VERSION_MAJOR >= 3
        if (font)
        {
            sf::Text text(*font, entry.name + " - " + std::to_string(entry.score), 20);
            text.setPosition({60.f, y});
            rows.push_back(text);
        }
#else
        sf::Text text;
        if (font)
            text.setFont(*font);
        text.setCharacterSize(20);
        text.setPosition({60.f, y});
        text.setString(entry.name + " - " + std::to_string(entry.score));
        rows.push_back(text);
#endif
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
#if SFML_VERSION_MAJOR >= 3
    if (title)
        target.draw(*title);
    for (auto& r : rows)
    {
        target.draw(r);
    }
#else
    if (title.getFont())
        target.draw(title);
    for (auto& r : rows)
    {
        if (r.getFont())
            target.draw(r);
    }
#endif
    backButton.draw(target);
}
