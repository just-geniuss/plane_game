#include "game/Player.hpp"
#include "game/Bullet.hpp"

Player::Player()
{
    size = {48.f, 48.f};
    shape.setSize(size);
    shape.setOrigin(size * 0.5f);
    shape.setFillColor(sf::Color(100, 180, 255));
}

void Player::update(float dt)
{
    position += velocity * dt;
    shape.setPosition(position);
}

void Player::draw(sf::RenderTarget& target)
{
    target.draw(shape);
}

void Player::handleInput(bool left, bool right, bool up, bool down, bool shoot, float dt, std::vector<Bullet>& bullets)
{
    velocity = {0.f, 0.f};
    if (left) velocity.x -= speed;
    if (right) velocity.x += speed;
    if (up) velocity.y -= speed;
    if (down) velocity.y += speed;

    // Clamp diagonal speed
    if (velocity.x != 0.f && velocity.y != 0.f)
    {
        velocity *= 0.7071f;
    }

    fireTimer += dt;
    if (shoot && fireTimer >= fireCooldown)
    {
        fireTimer = 0.f;
        Bullet bullet({position.x, position.y - size.y * 0.6f}, {0.f, -600.f}, true);
        bullets.push_back(bullet);
    }
}

void Player::damage(int amount)
{
    hp -= amount;
}

void Player::heal(int amount)
{
    hp += amount;
}
