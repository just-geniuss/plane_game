#pragma once

#include <vector>
#include "game/Enemy.hpp"

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

private:
    float elapsed{0.f};
    std::vector<SpawnInstruction> schedule;
};
