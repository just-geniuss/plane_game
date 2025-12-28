#include "core/Input.hpp"

#include <algorithm>
#include <variant>

namespace
{
Action stringToAction(const std::string& name)
{
    if (name == "MoveLeft") return Action::MoveLeft;
    if (name == "MoveRight") return Action::MoveRight;
    if (name == "MoveUp") return Action::MoveUp;
    if (name == "MoveDown") return Action::MoveDown;
    if (name == "Shoot") return Action::Shoot;
    if (name == "Pause") return Action::Pause;
    return Action::Pause;
}
}

void InputMapper::setBindings(const std::unordered_map<sf::Keyboard::Key, std::string>& settingsBindings)
{
    bindings.clear();
    for (const auto& kv : settingsBindings)
    {
        bindings[kv.first] = stringToAction(kv.second);
    }
}

void InputMapper::handleEvent(const sf::Event& event)
{
#if SFML_VERSION_MAJOR >= 3
    if (const auto* k = event.getIf<sf::Event::KeyPressed>())
    {
        auto it = bindings.find(k->code);
        if (it != bindings.end())
            activeActions[it->second] = true;
    }
    else if (const auto* k = event.getIf<sf::Event::KeyReleased>())
    {
        auto it = bindings.find(k->code);
        if (it != bindings.end())
            activeActions.erase(it->second);
    }
#else
    if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
    {
        auto it = bindings.find(event.key.code);
        if (it != bindings.end())
        {
            if (event.type == sf::Event::KeyPressed)
            {
                activeActions[it->second] = true;
            }
            else
            {
                activeActions.erase(it->second);
            }
        }
    }
#endif
}

void InputMapper::clearFrameState()
{
    // Keep continuous actions pressed keys alive; single-frame actions can be managed here if needed.
}
