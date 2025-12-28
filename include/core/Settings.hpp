#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

// Basic settings container that loads/saves key-value pairs from a simple ini-like file.

class Settings
{
public:
    bool load(const std::string& filename);
    bool save(const std::string& filename) const;

    sf::Vector2u resolution() const { return windowSize; }
    void setResolution(sf::Vector2u size) { windowSize = size; }

    bool fullscreen() const { return isFullscreen; }
    void setFullscreen(bool v) { isFullscreen = v; }

    bool vsync() const { return useVsync; }
    void setVsync(bool v) { useVsync = v; }

    unsigned int maxFps() const { return framerateLimit; }
    void setMaxFps(unsigned int fps) { framerateLimit = fps; }

    float musicVolume() const { return musicVol; }
    void setMusicVolume(float v) { musicVol = v; }

    float sfxVolume() const { return sfxVol; }
    void setSfxVolume(float v) { sfxVol = v; }

    const std::unordered_map<sf::Keyboard::Key, std::string>& keymap() const { return keyBindings; }
    void setKeyBinding(sf::Keyboard::Key key, const std::string& action);
    std::string actionForKey(sf::Keyboard::Key key) const;

private:
    sf::Vector2u windowSize{1280, 720};
    bool isFullscreen{false};
    bool useVsync{true};
    unsigned int framerateLimit{60};
    float musicVol{60.f};
    float sfxVol{70.f};
    std::unordered_map<sf::Keyboard::Key, std::string> keyBindings;
};
