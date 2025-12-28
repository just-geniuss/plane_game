#include "states/GameOverState.hpp"

#include "core/Game.hpp"
#include "states/MainMenuState.hpp"

#include <cctype>
#include <variant>

namespace
{
const std::string HIGHSCORE_PATH = "assets/config/highscores.txt";
}

GameOverState::GameOverState(Game& g, int finalScore, HighScoreSystem scores)
    : GameState(g), score(finalScore), highScores(std::move(scores))
{
    const sf::Font* font = nullptr;
    if (g.fonts().contains("default"))
        font = &g.fonts().get("default");

#if SFML_VERSION_MAJOR >= 3
    if (font)
    {
        title.emplace(*font, "Game Over", 32);
        inputLabel.emplace(*font, "Enter your name (letters A-Z), press Enter to submit:", 20);
        nameText.emplace(*font, nameBuffer, 28);
    }
#else
    if (font)
    {
        title.setFont(*font);
        inputLabel.setFont(*font);
        nameText.setFont(*font);
    }
    title.setCharacterSize(32);
    title.setString("Game Over");
    inputLabel.setCharacterSize(20);
    inputLabel.setString("Enter your name (letters A-Z), press Enter to submit:");
    nameText.setCharacterSize(28);
    nameText.setString(nameBuffer);
#endif

#if SFML_VERSION_MAJOR >= 3
    if (title) title->setPosition({40.f, 30.f});
    if (inputLabel) inputLabel->setPosition({40.f, 80.f});
    if (nameText) nameText->setPosition({40.f, 110.f});
#else
    title.setPosition({40.f, 30.f});
    inputLabel.setPosition({40.f, 80.f});
    nameText.setPosition({40.f, 110.f});
#endif

    backButton.setPosition({g.getWindow().getSize().x - 120.f, g.getWindow().getSize().y - 60.f});
    backButton.setSize({180.f, 44.f});
    backButton.setText("Main Menu", font, 22);
    Game& gRef = game;
    backButton.setCallback([&gRef]() { gRef.stateStack().clear(); gRef.stateStack().push<MainMenuState>(); });

    refreshTable();
}

void GameOverState::handleEvent(const sf::Event& event)
{
    #if SFML_VERSION_MAJOR >= 3
    if (const auto* txt = event.getIf<sf::Event::TextEntered>())
    {
        if (!submitted)
        {
            auto uni = txt->unicode;
            if (uni >= 'A' && uni <= 'Z')
            {
                if (nameBuffer.size() < 8)
                    nameBuffer.push_back(static_cast<char>(uni));
                if (nameText) nameText->setString(nameBuffer);
            }
            else if (uni >= 'a' && uni <= 'z')
            {
                if (nameBuffer.size() < 8)
                    nameBuffer.push_back(static_cast<char>(std::toupper(uni)));
                if (nameText) nameText->setString(nameBuffer);
            }
            else if (uni == 8 && !nameBuffer.empty())
            {
                nameBuffer.pop_back();
                if (nameText) nameText->setString(nameBuffer);
            }
            else if (uni == 13 || uni == '\r')
            {
                submitted = true;
                if (nameBuffer.empty()) nameBuffer = "AAA";
                highScores.submit(nameBuffer, score);
                highScores.save(HIGHSCORE_PATH);
                refreshTable();
            }
        }
    }
    #else
    if (event.type == sf::Event::TextEntered && !submitted)
    {
        if (event.text.unicode >= 'A' && event.text.unicode <= 'Z')
        {
            if (nameBuffer.size() < 8)
                nameBuffer.push_back(static_cast<char>(event.text.unicode));
            nameText.setString(nameBuffer);
        }
        else if (event.text.unicode >= 'a' && event.text.unicode <= 'z')
        {
            if (nameBuffer.size() < 8)
                nameBuffer.push_back(static_cast<char>(std::toupper(event.text.unicode)));
            nameText.setString(nameBuffer);
        }
        else if (event.text.unicode == 8 && !nameBuffer.empty())
        {
            nameBuffer.pop_back();
            nameText.setString(nameBuffer);
        }
        else if (event.text.unicode == 13 || event.text.unicode == '\r')
        {
            submitted = true;
            if (nameBuffer.empty()) nameBuffer = "AAA";
            highScores.submit(nameBuffer, score);
            highScores.save(HIGHSCORE_PATH);
            refreshTable();
        }
    }
    #endif
    backButton.handleEvent(event, game.getWindow());
}

void GameOverState::update(float)
{
}

void GameOverState::draw(sf::RenderTarget& target)
{
#if SFML_VERSION_MAJOR >= 3
    if (title) target.draw(*title);
    if (inputLabel) target.draw(*inputLabel);
    if (nameText) target.draw(*nameText);
    for (auto& r : rows)
    {
        target.draw(r);
    }
#else
    if (title.getFont())
        target.draw(title);
    if (inputLabel.getFont())
        target.draw(inputLabel);
    if (nameText.getFont())
        target.draw(nameText);
    for (auto& r : rows)
    {
        if (r.getFont())
            target.draw(r);
    }
#endif
    backButton.draw(target);
}

void GameOverState::refreshTable()
{
    rows.clear();
    const sf::Font* font = nullptr;
    if (game.fonts().contains("default"))
        font = &game.fonts().get("default");

    float y = 170.f;
    int rank = 1;
    for (const auto& entry : highScores.entries())
    {
#if SFML_VERSION_MAJOR >= 3
        if (font)
        {
            sf::Text t(*font, std::to_string(rank) + ". " + entry.name + " - " + std::to_string(entry.score), 20);
            t.setPosition({40.f, y});
            rows.push_back(t);
        }
#else
        sf::Text t;
        if (font) t.setFont(*font);
        t.setCharacterSize(20);
        t.setPosition({40.f, y});
        t.setString(std::to_string(rank) + ". " + entry.name + " - " + std::to_string(entry.score));
        rows.push_back(t);
#endif
        y += 28.f;
        ++rank;
    }
}
