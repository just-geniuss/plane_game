#pragma once

#include <SFML/Window.hpp>
#include <unordered_map>
#include <string>

enum class Action
{
    MoveLeft,
    MoveRight,
    MoveUp,
    MoveDown,
    Shoot,
    Pause
};

class InputMapper
{
public:
    void setBindings(const std::unordered_map<sf::Keyboard::Key, std::string>& settingsBindings);
    bool isActive(Action action) const { return activeActions.count(action) > 0; }
    void handleEvent(const sf::Event& event);
    void clearFrameState();

private:
    std::unordered_map<sf::Keyboard::Key, Action> bindings;
    std::unordered_map<Action, bool> activeActions;
};
