#pragma once

#include "game/Entity.hpp"
#include <SFML/Graphics.hpp>

namespace CollisionSystem
{
    inline bool intersects(const Entity& a, const Entity& b)
    {
        return a.bounds().intersects(b.bounds());
    }

    inline bool intersects(const sf::FloatRect& rect, const Entity& e)
    {
        return rect.intersects(e.bounds());
    }
}
