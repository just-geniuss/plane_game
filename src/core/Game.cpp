#include "core/Game.hpp"

#include <iostream>

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
    music.setLoop(true);
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
    sf::VideoMode mode(res.x, res.y);
    sf::Uint32 style = config.fullscreen() ? sf::Style::Fullscreen : sf::Style::Close;
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
        config.setResolution({1280, 720});
        config.setVsync(true);
        config.setMaxFps(60);
        config.setMusicVolume(60.f);
        config.setSfxVolume(70.f);
        config.setKeyBinding(sf::Keyboard::A, "MoveLeft");
        config.setKeyBinding(sf::Keyboard::D, "MoveRight");
        config.setKeyBinding(sf::Keyboard::W, "MoveUp");
        config.setKeyBinding(sf::Keyboard::S, "MoveDown");
        config.setKeyBinding(sf::Keyboard::Space, "Shoot");
        config.setKeyBinding(sf::Keyboard::Escape, "Pause");
        config.save(SETTINGS_PATH);
    }
}
