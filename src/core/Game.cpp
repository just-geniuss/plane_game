#include "core/Game.hpp"

#include <iostream>
#include <optional>
#include <variant>

#include "states/MainMenuState.hpp"

namespace
{
const std::string SETTINGS_PATH = "assets/config/settings.ini";
const std::string MUSIC_PATH = "assets/sounds/music.ogg";
const std::string FONT_DEFAULT = "assets/fonts/Default.ttf";
}

Game::Game() : states(*this)
{
    loadDefaults();
    setupWindow();

    if (fontManager.load("default", FONT_DEFAULT))
    {
        std::cout << "Loaded font: " << FONT_DEFAULT << "\n";
    }
    else
    {
        std::cout << "Warning: could not load font " << FONT_DEFAULT << "\n";
    }

    // Prepare audio
    #if SFML_VERSION_MAJOR >= 3
    music.setLooping(true);
    #else
    music.setLoop(true);
    #endif
    if (music.openFromFile(MUSIC_PATH))
    {
        music.setVolume(config.musicVolume());
        music.play();
    }

    // Input bindings
    inputMapper.setBindings(config.keymap());

    states.push<MainMenuState>();
}

void Game::run()
{
    sf::Clock clock;
    while (window.isOpen() && !shouldQuit)
    {
        float dt = clock.restart().asSeconds();
        processEvents();
        update(dt);
        render();
    }
}

void Game::processEvents()
{
    #if SFML_VERSION_MAJOR >= 3
    while (auto ev = window.pollEvent())
    {
        const sf::Event& event = *ev;
        if (event.is<sf::Event::Closed>())
        {
            window.close();
        }
        inputMapper.handleEvent(event);
        states.handleEvent(event);
    }
    #else
    sf::Event event{};
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        inputMapper.handleEvent(event);
        states.handleEvent(event);
    }
    #endif
}

void Game::update(float dt)
{
    states.update(dt);
}

void Game::render()
{
    window.clear(sf::Color(15, 15, 25));
    states.draw(window);
    window.display();
}

void Game::setupWindow()
{
    const auto res = config.resolution();
    #if SFML_VERSION_MAJOR >= 3
    sf::VideoMode mode;
    if (config.fullscreen())
        mode = sf::VideoMode::getDesktopMode();
    else
        mode = sf::VideoMode(sf::Vector2u(res.x, res.y));
    auto style = config.fullscreen() ? sf::Style::Fullscreen : sf::Style::Default;
    #else
    sf::VideoMode mode = config.fullscreen() ? sf::VideoMode::getDesktopMode() : sf::VideoMode(res.x, res.y);
    sf::Uint32 style = config.fullscreen() ? sf::Style::Fullscreen : sf::Style::Close;
    #endif
    window.create(mode, "Space Shooter", style);
    window.setVerticalSyncEnabled(config.vsync());
    if (!config.fullscreen())
        window.setFramerateLimit(config.maxFps());
}

void Game::loadDefaults()
{
    if (!config.load(SETTINGS_PATH))
    {
        // Apply sane defaults
        auto desktop = sf::VideoMode::getDesktopMode();
        config.setResolution({desktop.width, desktop.height});
        config.setFullscreen(true);
        config.setVsync(true);
        config.setMaxFps(60);
        config.setMusicVolume(60.f);
        config.setSfxVolume(70.f);
        config.setKeyBinding(sf::Keyboard::Key::A, "MoveLeft");
        config.setKeyBinding(sf::Keyboard::Key::D, "MoveRight");
        config.setKeyBinding(sf::Keyboard::Key::W, "MoveUp");
        config.setKeyBinding(sf::Keyboard::Key::S, "MoveDown");
        config.setKeyBinding(sf::Keyboard::Key::Space, "Shoot");
        config.setKeyBinding(sf::Keyboard::Key::Escape, "Pause");
        config.save(SETTINGS_PATH);
    }
}

void Game::applyAudioSettings()
{
    music.setVolume(config.musicVolume());
}
