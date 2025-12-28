#pragma once

#include "game/Entity.hpp"
#include <SFML/Graphics.hpp>

namespace CollisionSystem
{
    inline bool intersects(const Entity& a, const Entity& b)
    {
        #if SFML_VERSION_MAJOR >= 3
                const auto r1 = a.bounds();
                const auto r2 = b.bounds();
                return r1.left < r2.left + r2.width && r1.left + r1.width > r2.left &&
                           r1.top < r2.top + r2.height && r1.top + r1.height > r2.top;
        #else
                return a.bounds().intersects(b.bounds());
        #endif
    }

    inline bool intersects(const sf::FloatRect& rect, const Entity& e)
    {
        #if SFML_VERSION_MAJOR >= 3
                const auto r2 = e.bounds();
                return rect.left < r2.left + r2.width && rect.left + rect.width > r2.left &&
                           rect.top < r2.top + r2.height && rect.top + rect.height > r2.top;
        #else
                return rect.intersects(e.bounds());
        #endif
    }
}
