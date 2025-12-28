#include "game/WaveSystem.hpp"

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

void WaveSystem::update(float dt, std::vector<Enemy>& enemies, float playfieldWidth)
{
    elapsed += dt;
    while (!schedule.empty() && elapsed >= schedule.front().time)
    {
        auto inst = schedule.front();
        schedule.erase(schedule.begin());
        // Randomize horizontal position within bounds
        inst.position.x = std::max(60.f, std::min(playfieldWidth - 60.f, inst.position.x));
        enemies.emplace_back(inst.type, inst.position);
    }

    // Endless trickle after scripted schedule
    if (elapsed > 10.f)
    {
        static float timer = 0.f;
        timer += dt;
        if (timer > 1.5f)
        {
            timer = 0.f;
            float x = 80.f + static_cast<float>(std::rand() % static_cast<int>(playfieldWidth - 160.f));
            enemies.emplace_back(EnemyType::Basic, sf::Vector2f{x, -40.f});
        }
    }
}
