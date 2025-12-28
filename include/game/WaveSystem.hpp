#pragma once

#include <vector>
#include "game/Enemy.hpp"
#include "core/Settings.hpp"

struct SpawnInstruction
{
    float time;
    EnemyType type;
    sf::Vector2f position;
};

class WaveSystem
{
public:
    WaveSystem();
    void update(float dt, std::vector<Enemy>& enemies, float playfieldWidth);
    void setDifficulty(Difficulty d);

private:
    void spawnEnemy(std::vector<Enemy>& enemies, EnemyType type, sf::Vector2f pos) const;

    Difficulty difficulty{Difficulty::Easy};
    float sizeScale{1.f};
    float endlessInterval{1.5f};
    float bossInterval{12.f};
    float extraBossChance{0.f};
    bool bossOnly{false};
    float endlessTimer{0.f};
    float bossTimer{0.f};
    float elapsed{0.f};
    std::vector<SpawnInstruction> schedule;
};
