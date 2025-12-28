#pragma once

#include "game/Entity.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class Bullet;

class Player : public Entity
{
public:
    Player();

    void update(float dt) override;
    void draw(sf::RenderTarget& target) override;

    void handleInput(bool left, bool right, bool up, bool down, bool shoot, float dt, std::vector<Bullet>& bullets);

    int health() const { return hp; }
    void damage(int amount);
    void heal(int amount);

    void setFireRate(float rate) { fireCooldown = rate; }

private:
    sf::RectangleShape shape;
    sf::Texture texture;
    sf::Sprite sprite;
    bool textureLoaded{false};
    int hp{5};
    float speed{300.f};
    float fireCooldown{0.25f};
    float fireTimer{0.f};
};
