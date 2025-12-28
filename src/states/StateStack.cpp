#include "states/StateStack.hpp"
#include "core/Game.hpp"

StateStack::StateStack(Game& g) : game(g) {}

void StateStack::pop()
{
    if (!states.empty())
        states.pop_back();
}

void StateStack::clear()
{
    states.clear();
}

void StateStack::handleEvent(const sf::Event& event)
{
    if (!states.empty())
    {
        states.back()->handleEvent(event);
    }
}

void StateStack::update(float dt)
{
    if (!states.empty())
    {
        states.back()->update(dt);
    }
}

void StateStack::draw(sf::RenderTarget& target)
{
    if (!states.empty())
    {
        states.back()->draw(target);
    }
}
