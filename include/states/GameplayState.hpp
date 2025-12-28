#pragma once

#include "states/GameState.hpp"
#include "game/Player.hpp"
#include "game/Enemy.hpp"
#include "game/Bullet.hpp"
#include "game/PowerUp.hpp"
#include "game/Explosion.hpp"
#include "game/WaveSystem.hpp"
#include "ui/HUD.hpp"
#include "systems/HighScoreSystem.hpp"
#include <vector>

class GameplayState : public GameState
{
public:
    explicit GameplayState(Game& game);

    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderTarget& target) override;

private:
    void handleCollisions();
    void clampPlayerToView();
    void spawnEnemyFire(float dt);

    Player player;
    std::vector<Bullet> playerBullets;
    std::vector<Bullet> enemyBullets;
    std::vector<Enemy> enemies;
    std::vector<PowerUp> powerups;
    std::vector<Explosion> explosions;

    WaveSystem waves;
    HUD hud;
    HighScoreSystem highscores;

    int score{0};
    int waveIndex{1};
    float enemyFireTimer{0.f};
};
