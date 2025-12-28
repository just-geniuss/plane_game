#pragma once

#include "game/Entity.hpp"
#include <SFML/Graphics.hpp>

enum class EnemyType
{
    Basic,
    Agile,
    Heavy,
    MiniBoss
};

class Enemy : public Entity
{
public:
    Enemy(EnemyType type, const sf::Vector2f& pos);

    void update(float dt) override;
    void draw(sf::RenderTarget& target) override;

    EnemyType type() const { return enemyType; }
    int health() const { return hp; }
    void damage(int amount);

    bool canFire() const { return fireTimer >= fireCooldown; }
    void resetFire() { fireTimer = 0.f; }

private:
    void ensureTexturesLoaded();
    void setupSprite();

    EnemyType enemyType{EnemyType::Basic};
    int hp{2};
    float speed{120.f};
    float fireCooldown{1.5f};
    float fireTimer{0.f};
    sf::Vector2f baseSize{0.f, 0.f};
    sf::RectangleShape shape;
    sf::Sprite sprite;
    bool textureLoaded{false};

    static bool texturesReady;
    static sf::Texture texture1;
    static sf::Texture texture2;
    static sf::Texture textureBoss;
};
