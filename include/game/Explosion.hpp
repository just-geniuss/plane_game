#pragma once

#include "game/Entity.hpp"
#include <SFML/Graphics.hpp>

class Explosion : public Entity
{
public:
    explicit Explosion(const sf::Vector2f& pos);

    void update(float dt) override;
    void draw(sf::RenderTarget& target) override;

    bool finished() const { return lifetime <= 0.f; }

private:
    float lifetime{0.6f};
    sf::CircleShape shape;
};
