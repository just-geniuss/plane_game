#include "states/PauseState.hpp"

#include "core/Game.hpp"
#include "states/SettingsState.hpp"
#include "states/MainMenuState.hpp"

#include <variant>

PauseState::PauseState(Game& g) : GameState(g)
{
    const sf::Font* font = nullptr;
    if (g.fonts().contains("default"))
        font = &g.fonts().get("default");

#if SFML_VERSION_MAJOR >= 3
    if (font)
    {
        title.emplace(*font, "Paused", 30);
        title->setPosition({g.getWindow().getSize().x * 0.5f - 50.f, g.getWindow().getSize().y * 0.3f});
    }
#else
    if (font)
        title.setFont(*font);
    title.setString("Paused");
    title.setCharacterSize(30);
    title.setPosition({g.getWindow().getSize().x * 0.5f - 50.f, g.getWindow().getSize().y * 0.3f});
#endif

    buttons.resize(3);
    float x = g.getWindow().getSize().x * 0.5f;
    float y = g.getWindow().getSize().y * 0.45f;
    std::vector<std::string> labels = {"Resume", "Settings", "Main Menu"};
    for (std::size_t i = 0; i < buttons.size(); ++i)
    {
        buttons[i].setPosition({x, y + 60.f * static_cast<float>(i)});
        buttons[i].setSize({230.f, 44.f});
        buttons[i].setText(labels[i], font, 22);
    }

    buttons[0].setCallback([this]() { game.stateStack().pop(); });
    buttons[1].setCallback([this]() { game.stateStack().push<SettingsState>(); });
    Game& gRef = game;
    buttons[2].setCallback([&gRef]() { gRef.stateStack().clear(); gRef.stateStack().push<MainMenuState>(); });
}

void PauseState::handleEvent(const sf::Event& event)
{
    for (auto& b : buttons)
        b.handleEvent(event, game.getWindow());
#if SFML_VERSION_MAJOR >= 3
    if (const auto* key = event.getIf<sf::Event::KeyPressed>())
    {
        if (key->code == sf::Keyboard::Key::Escape)
            game.stateStack().pop();
    }
#else
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    {
        game.stateStack().pop();
    }
#endif
}

void PauseState::update(float)
{
}

void PauseState::draw(sf::RenderTarget& target)
{
#if SFML_VERSION_MAJOR >= 3
    if (title)
        target.draw(*title);
#else
    if (title.getFont())
        target.draw(title);
#endif
    for (auto& b : buttons)
        b.draw(target);
}
