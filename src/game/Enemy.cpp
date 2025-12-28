#include "game/Enemy.hpp"

Enemy::Enemy(EnemyType t, const sf::Vector2f& pos) : enemyType(t)
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
    shape.setSize(size);
    shape.setOrigin(size * 0.5f);
    shape.setPosition(position);
}

void Enemy::update(float dt)
{
    fireTimer += dt;
    position += sf::Vector2f(0.f, speed * dt);
    shape.setPosition(position);
}

void Enemy::draw(sf::RenderTarget& target)
{
    target.draw(shape);
}

void Enemy::damage(int amount)
{
    hp -= amount;
}
