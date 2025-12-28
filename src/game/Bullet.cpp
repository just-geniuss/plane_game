#include "game/Bullet.hpp"

Bullet::Bullet(const sf::Vector2f& pos, const sf::Vector2f& vel, bool fromPlayer)
{
    position = pos;
    velocity = vel;
    playerOwned = fromPlayer;
    size = {8.f, 16.f};
    shape.setSize(size);
    shape.setOrigin(size * 0.5f);
    shape.setFillColor(playerOwned ? sf::Color::Cyan : sf::Color::Red);
    shape.setPosition(position);
}

void Bullet::update(float dt)
{
    position += velocity * dt;
    shape.setPosition(position);
}

void Bullet::draw(sf::RenderTarget& target)
{
    target.draw(shape);
}
