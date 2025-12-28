#pragma once

#include "game/Entity.hpp"

class Bullet : public Entity
{
public:
    Bullet(const sf::Vector2f& pos, const sf::Vector2f& vel, bool fromPlayer);

    void update(float dt) override;
    void draw(sf::RenderTarget& target) override;

    bool isFromPlayer() const { return playerOwned; }
    int damage() const { return 1; }

private:
    bool playerOwned{true};
    sf::RectangleShape shape;
};
