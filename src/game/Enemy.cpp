#include "game/Enemy.hpp"

#include <algorithm>
#include <cstdlib>

bool Enemy::texturesReady = false;
sf::Texture Enemy::texture1;
sf::Texture Enemy::texture2;
sf::Texture Enemy::textureBoss;

Enemy::Enemy(EnemyType t, const sf::Vector2f& pos, float sizeScale) : enemyType(t)
{
    position = pos;
    switch (enemyType)
    {
    case EnemyType::Basic:
        size = {40.f, 40.f};
        hp = 2;
        speed = 120.f;
        fireCooldown = 1.5f;
        shape.setFillColor(sf::Color(220, 80, 80));
        break;
    case EnemyType::Agile:
        size = {32.f, 32.f};
        hp = 2;
        speed = 180.f;
        fireCooldown = 1.0f;
        shape.setFillColor(sf::Color(220, 140, 80));
        break;
    case EnemyType::Heavy:
        size = {56.f, 56.f};
        hp = 5;
        speed = 80.f;
        fireCooldown = 2.0f;
        shape.setFillColor(sf::Color(180, 60, 140));
        break;
    case EnemyType::MiniBoss:
        size = {96.f, 96.f};
        hp = 12;
        speed = 60.f;
        fireCooldown = 1.2f;
        shape.setFillColor(sf::Color(120, 40, 200));
        break;
    }
    baseSize = size * sizeScale;
    size = baseSize;
    shape.setSize(size);
    shape.setOrigin(size * 0.5f);
    shape.setPosition(position);

    ensureTexturesLoaded();
    setupSprite();
}

void Enemy::update(float dt)
{
    fireTimer += dt;
    position += sf::Vector2f(0.f, speed * dt);
    if (textureLoaded)
        sprite.setPosition(position);
    else
        shape.setPosition(position);
}

void Enemy::draw(sf::RenderTarget& target)
{
    if (textureLoaded)
        target.draw(sprite);
    else
        target.draw(shape);
}

void Enemy::damage(int amount)
{
    hp -= amount;
}

void Enemy::ensureTexturesLoaded()
{
    if (texturesReady)
        return;

#if SFML_VERSION_MAJOR >= 3
    const bool ok1 = texture1.openFromFile("assets/textures/enemy_1.png");
    const bool ok2 = texture2.openFromFile("assets/textures/enemy_2.png");
    const bool okBoss = textureBoss.openFromFile("assets/textures/enemy_boss.png");
#else
    const bool ok1 = texture1.loadFromFile("assets/textures/enemy_1.png");
    const bool ok2 = texture2.loadFromFile("assets/textures/enemy_2.png");
    const bool okBoss = textureBoss.loadFromFile("assets/textures/enemy_boss.png");
#endif

    texture1.setSmooth(true);
    texture2.setSmooth(true);
    textureBoss.setSmooth(true);

    texturesReady = ok1 && ok2 && okBoss;
}

void Enemy::setupSprite()
{
    if (!texturesReady)
        return;

    const sf::Texture* chosen = nullptr;
    if (enemyType == EnemyType::MiniBoss)
    {
        chosen = &textureBoss;
    }
    else
    {
        chosen = (std::rand() % 2 == 0) ? &texture1 : &texture2;
    }

    const auto texSize = chosen->getSize();
    if (texSize.x == 0 || texSize.y == 0)
        return;

    sprite.setTexture(*chosen);

    const float spriteScaleMultiplier = 2.5f; // enlarge visible sprite ~2.5x
    const float hitboxScaleMultiplier = 1.5f; // enlarge collision box ~1.5x

    const sf::Vector2f targetSize = baseSize * spriteScaleMultiplier;
    const float scale = std::min(targetSize.x / static_cast<float>(texSize.x),
                                 targetSize.y / static_cast<float>(texSize.y));
    sprite.setScale(scale, scale);

    const sf::FloatRect local = sprite.getLocalBounds();
    size = baseSize * hitboxScaleMultiplier; // collision bounds
    shape.setSize(size);
    shape.setOrigin(size * 0.5f);

    sprite.setOrigin(local.width * 0.5f, local.height * 0.5f);
    sprite.setPosition(position);
    textureLoaded = true;
}
