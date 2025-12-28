#include "game/Player.hpp"
#include "game/Bullet.hpp"

#include <algorithm>

Player::Player()
{
    size = {48.f, 48.f};
    shape.setSize(size);
    shape.setOrigin(size * 0.5f);
    shape.setFillColor(sf::Color(100, 180, 255));

#if SFML_VERSION_MAJOR >= 3
    if (texture.openFromFile("assets/textures/player.png"))
#else
    if (texture.loadFromFile("assets/textures/player.png"))
#endif
    {
        texture.setSmooth(true);
        sprite.setTexture(texture);

        const auto texSize = texture.getSize();
        if (texSize.x > 0 && texSize.y > 0)
        {
            const float textureScale = 2.00f; // enlarge sprite ~1.75x relative to default 48x48
            const sf::Vector2f targetSize = size * textureScale;
            const float scale = std::min(targetSize.x / static_cast<float>(texSize.x),
                                         targetSize.y / static_cast<float>(texSize.y));

            sprite.setScale(scale, scale);

            // Update collision size to match the scaled sprite bounds
            const sf::FloatRect local = sprite.getLocalBounds();
            size = {local.width * scale, local.height * scale};
            shape.setSize(size);
            shape.setOrigin(size * 0.5f);

            sprite.setOrigin(local.width * 0.5f, local.height * 0.5f);
            textureLoaded = true;
        }
    }
}

void Player::update(float dt)
{
    position += velocity * dt;
    if (textureLoaded)
        sprite.setPosition(position);
    else
        shape.setPosition(position);
}

void Player::draw(sf::RenderTarget& target)
{
    if (textureLoaded)
        target.draw(sprite);
    else
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
