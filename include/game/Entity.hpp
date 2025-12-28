#pragma once

#include <SFML/Graphics.hpp>

class Entity
{
public:
    virtual ~Entity() = default;

    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderTarget& target) = 0;

    void setPosition(const sf::Vector2f& p) { position = p; }
    sf::Vector2f getPosition() const { return position; }

    void setVelocity(const sf::Vector2f& v) { velocity = v; }
    sf::Vector2f getVelocity() const { return velocity; }

    void setSize(const sf::Vector2f& s) { size = s; }
    sf::Vector2f getSize() const { return size; }

    sf::FloatRect bounds() const { return {position - size * 0.5f, size}; }

protected:
    sf::Vector2f position{0.f, 0.f};
    sf::Vector2f velocity{0.f, 0.f};
    sf::Vector2f size{32.f, 32.f};
};
