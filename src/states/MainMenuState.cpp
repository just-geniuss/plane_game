#include "states/MainMenuState.hpp"

#include "core/Game.hpp"
#include "states/GameplayState.hpp"
#include "states/SettingsState.hpp"
#include "states/HighScoreState.hpp"

MainMenuState::MainMenuState(Game& g) : GameState(g)
{
    buttons.resize(4);
    const sf::Font* font = nullptr;
    if (g.fonts().contains("default"))
    {
        font = &g.fonts().get("default");
    }

    float x = g.getWindow().getSize().x * 0.5f;
    float y = g.getWindow().getSize().y * 0.4f;
    const float step = 70.f;

    std::vector<std::string> labels = {"Play", "Settings", "High Scores", "Quit"};
    for (std::size_t i = 0; i < buttons.size(); ++i)
    {
        buttons[i].setPosition({x, y + step * static_cast<float>(i)});
        buttons[i].setSize({240.f, 48.f});
        buttons[i].setText(labels[i], font, 24);
    }

    buttons[0].setCallback([this]() { game.stateStack().push<GameplayState>(); });
    buttons[1].setCallback([this]() { game.stateStack().push<SettingsState>(); });
    buttons[2].setCallback([this]() { game.stateStack().push<HighScoreState>(); });
    buttons[3].setCallback([this]() { game.quit(); });
}

void MainMenuState::handleEvent(const sf::Event& event)
{
    for (auto& b : buttons)
    {
        b.handleEvent(event, game.getWindow());
    }
}

void MainMenuState::update(float)
{
}

void MainMenuState::draw(sf::RenderTarget& target)
{
    for (auto& b : buttons)
    {
        b.draw(target);
    }
}
