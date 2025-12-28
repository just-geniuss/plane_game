#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <string>

#include "core/ResourceManager.hpp"
#include "core/Settings.hpp"
#include "core/Input.hpp"
#include "states/StateStack.hpp"

class Game
{
public:
    Game();
    void run();

    sf::RenderWindow& getWindow() { return window; }
    const sf::RenderWindow& getWindow() const { return window; }

    ResourceManager<sf::Texture>& textures() { return textureManager; }
    ResourceManager<sf::Font>& fonts() { return fontManager; }
    ResourceManager<sf::SoundBuffer>& sounds() { return soundManager; }

    Settings& settings() { return config; }
    const Settings& settings() const { return config; }

    StateStack& stateStack() { return states; }
    InputMapper& input() { return inputMapper; }

    void applyAudioSettings();

    void quit() { shouldQuit = true; }

private:
    void processEvents();
    void update(float dt);
    void render();
    void setupWindow();
    void loadDefaults();

    sf::RenderWindow window;
    ResourceManager<sf::Texture> textureManager;
    ResourceManager<sf::Font> fontManager;
    ResourceManager<sf::SoundBuffer> soundManager;
    sf::Music music;

    Settings config;
    InputMapper inputMapper;
    StateStack states;
    bool shouldQuit{false};
};
