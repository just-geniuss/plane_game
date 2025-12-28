#include "game/PowerUp.hpp"

PowerUp::PowerUp(PowerUpType type, const sf::Vector2f& pos) : powerType(type)
{
    position = pos;
    size = {24.f, 24.f};
    shape.setRadius(size.x * 0.5f);
    shape.setOrigin({shape.getRadius(), shape.getRadius()});
    switch (powerType)
    {
    case PowerUpType::Shield: shape.setFillColor(sf::Color(80, 200, 255)); break;
    case PowerUpType::Damage: shape.setFillColor(sf::Color(255, 120, 80)); break;
    case PowerUpType::FireRate: shape.setFillColor(sf::Color(255, 220, 80)); break;
    case PowerUpType::Heal: shape.setFillColor(sf::Color(120, 255, 120)); break;
    }
    shape.setPosition(position);
}

void PowerUp::update(float dt)
{
    position.y += 80.f * dt;
    shape.setPosition(position);
}

void PowerUp::draw(sf::RenderTarget& target)
{
    target.draw(shape);
}
