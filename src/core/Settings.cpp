#include "core/Settings.hpp"

#include <fstream>
#include <sstream>

namespace
{
std::unordered_map<std::string, sf::Keyboard::Key> makeKeyLookup()
{
    return {
        {"A", sf::Keyboard::A}, {"D", sf::Keyboard::D}, {"W", sf::Keyboard::W}, {"S", sf::Keyboard::S},
        {"Left", sf::Keyboard::Left}, {"Right", sf::Keyboard::Right}, {"Up", sf::Keyboard::Up}, {"Down", sf::Keyboard::Down},
        {"Space", sf::Keyboard::Space}, {"Escape", sf::Keyboard::Escape}, {"Enter", sf::Keyboard::Enter},
    };
}

std::string keyToString(sf::Keyboard::Key key)
{
    for (const auto& pair : makeKeyLookup())
    {
        if (pair.second == key)
        {
            return pair.first;
        }
    }
    return "Unknown";
}
}

bool Settings::load(const std::string& filename)
{
    std::ifstream in(filename);
    if (!in)
    {
        return false;
    }

    auto lookup = makeKeyLookup();

    std::string line;
    while (std::getline(in, line))
    {
        if (line.empty() || line[0] == '#')
            continue;
        auto pos = line.find('=');
        if (pos == std::string::npos)
            continue;
        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);

        if (key == "resolution")
        {
            unsigned int w = 0, h = 0;
            char x = 0;
            std::istringstream iss(value);
            if (iss >> w >> x >> h)
                windowSize = {w, h};
        }
        else if (key == "fullscreen")
        {
            isFullscreen = (value == "1" || value == "true");
        }
        else if (key == "vsync")
        {
            useVsync = (value == "1" || value == "true");
        }
        else if (key == "max_fps")
        {
            framerateLimit = static_cast<unsigned int>(std::stoi(value));
        }
        else if (key == "music_volume")
        {
            musicVol = std::stof(value);
        }
        else if (key == "sfx_volume")
        {
            sfxVol = std::stof(value);
        }
        else if (key.rfind("key_", 0) == 0)
        {
            std::string action = key.substr(4);
            auto it = lookup.find(value);
            if (it != lookup.end())
            {
                keyBindings[it->second] = action;
            }
        }
    }
    return true;
}

bool Settings::save(const std::string& filename) const
{
    std::ofstream out(filename);
    if (!out)
        return false;

    out << "resolution=" << windowSize.x << "x" << windowSize.y << "\n";
    out << "fullscreen=" << (isFullscreen ? 1 : 0) << "\n";
    out << "vsync=" << (useVsync ? 1 : 0) << "\n";
    out << "max_fps=" << framerateLimit << "\n";
    out << "music_volume=" << musicVol << "\n";
    out << "sfx_volume=" << sfxVol << "\n";

    for (const auto& kv : keyBindings)
    {
        out << "key_" << kv.second << "=" << keyToString(kv.first) << "\n";
    }
    return true;
}

void Settings::setKeyBinding(sf::Keyboard::Key key, const std::string& action)
{
    keyBindings[key] = action;
}

std::string Settings::actionForKey(sf::Keyboard::Key key) const
{
    auto it = keyBindings.find(key);
    if (it != keyBindings.end())
    {
        return it->second;
    }
    return {};
}
