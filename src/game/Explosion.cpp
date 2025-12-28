#include "game/Explosion.hpp"

#include <cstdint>

Explosion::Explosion(const sf::Vector2f& pos)
{
    position = pos;
    size = {24.f, 24.f};
    shape.setRadius(size.x * 0.5f);
    shape.setOrigin(sf::Vector2f(shape.getRadius(), shape.getRadius()));
    shape.setFillColor(sf::Color(255, 180, 50, 180));
    shape.setPosition(position);
}

void Explosion::update(float dt)
{
    lifetime -= dt;
    float scale = std::max(0.f, lifetime) / 0.6f;
    shape.setScale(sf::Vector2f(1.f + (1.f - scale), 1.f + (1.f - scale)));
    shape.setFillColor(sf::Color(255, 180, 50, static_cast<std::uint8_t>(180 * scale)));
}

void Explosion::draw(sf::RenderTarget& target)
{
    target.draw(shape);
}
