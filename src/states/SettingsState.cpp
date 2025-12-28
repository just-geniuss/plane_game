#include "states/SettingsState.hpp"

#include "core/Game.hpp"
#include <sstream>

namespace
{
const std::string SETTINGS_PATH = "assets/config/settings.ini";
}

SettingsState::SettingsState(Game& g) : GameState(g)
{
    const sf::Font* font = nullptr;
    if (g.fonts().contains("default"))
        font = &g.fonts().get("default");

    float x = g.getWindow().getSize().x * 0.5f;
    float y = g.getWindow().getSize().y * 0.35f;
    buttons.resize(4);
    std::vector<std::string> labels = {"Toggle VSync", "Music Volume +", "Music Volume -", "Back"};
    for (std::size_t i = 0; i < buttons.size(); ++i)
    {
        buttons[i].setPosition({x, y + 60.f * static_cast<float>(i)});
        buttons[i].setSize({260.f, 44.f});
        buttons[i].setText(labels[i], font, 22);
    }

    buttons[0].setCallback([this]() {
        auto& s = game.settings();
        s.setVsync(!s.vsync());
        game.getWindow().setVerticalSyncEnabled(s.vsync());
        refreshTexts();
        s.save(SETTINGS_PATH);
    });
    buttons[1].setCallback([this]() {
        auto& s = game.settings();
        s.setMusicVolume(std::min(100.f, s.musicVolume() + 5.f));
        refreshTexts();
        s.save(SETTINGS_PATH);
    });
    buttons[2].setCallback([this]() {
        auto& s = game.settings();
        s.setMusicVolume(std::max(0.f, s.musicVolume() - 5.f));
        refreshTexts();
        s.save(SETTINGS_PATH);
    });
    buttons[3].setCallback([this]() {
        game.stateStack().pop();
    });

#if SFML_VERSION_MAJOR >= 3
    if (font)
    {
        title.emplace(*font, "Settings", 32);
        title->setPosition({x - 60.f, y - 80.f});

        details.emplace(*font, "", 18);
        details->setPosition({x - 120.f, y - 40.f});
    }
#else
    if (font)
    {
        title.setFont(*font);
        details.setFont(*font);
    }
    title.setString("Settings");
    title.setCharacterSize(32);
    title.setPosition({x - 60.f, y - 80.f});

    details.setCharacterSize(18);
    details.setPosition({x - 120.f, y - 40.f});
#endif
    refreshTexts();
}

void SettingsState::refreshTexts()
{
    std::ostringstream oss;
    oss << "VSync: " << (game.settings().vsync() ? "On" : "Off") << "\n";
    oss << "Music volume: " << static_cast<int>(game.settings().musicVolume()) << "%" << "\n";
#if SFML_VERSION_MAJOR >= 3
    if (details)
        details->setString(oss.str());
#else
    details.setString(oss.str());
#endif
}

void SettingsState::handleEvent(const sf::Event& event)
{
    for (auto& b : buttons)
        b.handleEvent(event, game.getWindow());
}

void SettingsState::update(float)
{
}

void SettingsState::draw(sf::RenderTarget& target)
{
#if SFML_VERSION_MAJOR >= 3
    if (title)
        target.draw(*title);
    if (details)
        target.draw(*details);
#else
    if (title.getFont())
        target.draw(title);
    if (details.getFont())
        target.draw(details);
#endif
    for (auto& b : buttons)
        b.draw(target);
}
