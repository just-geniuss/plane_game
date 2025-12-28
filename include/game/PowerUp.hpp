#pragma once

#include "game/Entity.hpp"
#include <SFML/Graphics.hpp>

enum class PowerUpType
{
    Shield,
    Damage,
    FireRate,
    Heal
};

class PowerUp : public Entity
{
public:
    PowerUp(PowerUpType type, const sf::Vector2f& pos);

    void update(float dt) override;
    void draw(sf::RenderTarget& target) override;

    PowerUpType type() const { return powerType; }

private:
    PowerUpType powerType{PowerUpType::Shield};
    sf::CircleShape shape;
};
