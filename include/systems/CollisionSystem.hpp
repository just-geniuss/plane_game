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
        return r1.position.x < r2.position.x + r2.size.x && r1.position.x + r1.size.x > r2.position.x &&
               r1.position.y < r2.position.y + r2.size.y && r1.position.y + r1.size.y > r2.position.y;
        #else
                return a.bounds().intersects(b.bounds());
        #endif
    }

    inline bool intersects(const sf::FloatRect& rect, const Entity& e)
    {
        #if SFML_VERSION_MAJOR >= 3
                const auto r2 = e.bounds();
        return rect.position.x < r2.position.x + r2.size.x && rect.position.x + rect.size.x > r2.position.x &&
               rect.position.y < r2.position.y + r2.size.y && rect.position.y + rect.size.y > r2.position.y;
        #else
                return rect.intersects(e.bounds());
        #endif
    }
}
