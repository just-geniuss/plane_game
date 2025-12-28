#pragma once

#include "game/Entity.hpp"
#include <SFML/Graphics.hpp>

namespace CollisionSystem
{
    inline bool intersects(const Entity& a, const Entity& b)
    {
#if SFML_VERSION_MAJOR >= 3
        return sf::intersects(a.bounds(), b.bounds());
#else
        return a.bounds().intersects(b.bounds());
#endif
    }

    inline bool intersects(const sf::FloatRect& rect, const Entity& e)
    {
#if SFML_VERSION_MAJOR >= 3
        return sf::intersects(rect, e.bounds());
#else
        return rect.intersects(e.bounds());
#endif
    }
}
