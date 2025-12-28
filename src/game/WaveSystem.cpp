#include "game/WaveSystem.hpp"

#include <algorithm>
#include <cstdlib>

WaveSystem::WaveSystem()
{
    // Simple scripted wave schedule
    schedule = {
        {1.f, EnemyType::Basic, {200.f, -40.f}},
        {2.f, EnemyType::Basic, {400.f, -40.f}},
        {3.f, EnemyType::Agile, {600.f, -40.f}},
        {4.f, EnemyType::Basic, {800.f, -40.f}},
        {5.f, EnemyType::Heavy, {500.f, -60.f}},
        {7.f, EnemyType::MiniBoss, {640.f, -100.f}},
    };
}

void WaveSystem::setDifficulty(Difficulty d)
{
    difficulty = d;
    switch (difficulty)
    {
    case Difficulty::Easy:
        sizeScale = 1.f;
        endlessInterval = 1.5f;
        bossInterval = 12.f;
        extraBossChance = 0.f;
        bossOnly = false;
        break;
    case Difficulty::Medium:
        sizeScale = 0.85f;
        endlessInterval = 1.0f;
        bossInterval = 10.f;
        extraBossChance = 0.15f;
        bossOnly = false;
        break;
    case Difficulty::Hard:
        sizeScale = 0.7f;
        endlessInterval = 0.8f;
        bossInterval = 8.f;
        extraBossChance = 0.3f;
        bossOnly = false;
        break;
    case Difficulty::Legend:
        sizeScale = 0.75f;
        endlessInterval = 2.5f;
        bossInterval = 5.f;
        extraBossChance = 1.f;
        bossOnly = true;
        break;
    }

    if (bossOnly)
    {
        for (auto& inst : schedule)
            inst.type = EnemyType::MiniBoss;
    }
}

void WaveSystem::update(float dt, std::vector<Enemy>& enemies, float playfieldWidth)
{
    elapsed += dt;
    while (!schedule.empty() && elapsed >= schedule.front().time)
    {
        auto inst = schedule.front();
        schedule.erase(schedule.begin());
        // Randomize horizontal position within bounds
        inst.position.x = std::max(60.f, std::min(playfieldWidth - 60.f, inst.position.x));
        spawnEnemy(enemies, inst.type, inst.position);
    }

    // Endless trickle after scripted schedule
    if (elapsed > 10.f)
    {
        endlessTimer += dt;
        bossTimer += dt;

        if (bossOnly)
        {
            if (bossTimer > bossInterval)
            {
                bossTimer = 0.f;
                float x = 80.f + static_cast<float>(std::rand() % static_cast<int>(playfieldWidth - 160.f));
                spawnEnemy(enemies, EnemyType::MiniBoss, {x, -80.f});
            }
            return;
        }

        if (endlessTimer > endlessInterval)
        {
            endlessTimer = 0.f;
            float x = 80.f + static_cast<float>(std::rand() % static_cast<int>(playfieldWidth - 160.f));
            EnemyType type = (std::rand() % 4 == 0) ? EnemyType::Agile : EnemyType::Basic;
            spawnEnemy(enemies, type, {x, -40.f});
        }

        if (bossTimer > bossInterval)
        {
            bossTimer = 0.f;
            if ((std::rand() / static_cast<float>(RAND_MAX)) < extraBossChance)
            {
                float x = 120.f + static_cast<float>(std::rand() % static_cast<int>(playfieldWidth - 240.f));
                spawnEnemy(enemies, EnemyType::MiniBoss, {x, -80.f});
            }
        }
    }
}

void WaveSystem::spawnEnemy(std::vector<Enemy>& enemies, EnemyType type, sf::Vector2f pos) const
{
    enemies.emplace_back(type, pos, sizeScale);
}
