#include "states/GameplayState.hpp"

#include "core/Game.hpp"
#include "states/PauseState.hpp"
#include "states/GameOverState.hpp"
#include "systems/CollisionSystem.hpp"

#include <algorithm>
#include <cmath>
#include <variant>

namespace
{
const std::string HIGHSCORE_PATH = "assets/config/highscores.txt";
}

GameplayState::GameplayState(Game& g) : GameState(g)
{
    player.setPosition({static_cast<float>(g.getWindow().getSize().x) * 0.5f, static_cast<float>(g.getWindow().getSize().y) - 80.f});
    hud.setFont(g.fonts().contains("default") ? &g.fonts().get("default") : nullptr);
    highscores.load(HIGHSCORE_PATH);
}

void GameplayState::handleEvent(const sf::Event& event)
{
    #if SFML_VERSION_MAJOR >= 3
        if (const auto* key = event.getIf<sf::Event::KeyPressed>())
        {
            if (key->code == sf::Keyboard::Key::Escape)
                game.stateStack().push<PauseState>();
        }
    #else
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        {
            game.stateStack().push<PauseState>();
        }
    #endif
}

void GameplayState::update(float dt)
{
    bool left = game.input().isActive(Action::MoveLeft);
    bool right = game.input().isActive(Action::MoveRight);
    bool up = game.input().isActive(Action::MoveUp);
    bool down = game.input().isActive(Action::MoveDown);
    bool shoot = game.input().isActive(Action::Shoot);

    player.handleInput(left, right, up, down, shoot, dt, playerBullets);
    player.update(dt);
    clampPlayerToView();

    for (auto& b : playerBullets) b.update(dt);
    for (auto& b : enemyBullets) b.update(dt);
    for (auto& e : enemies) e.update(dt);
    for (auto& p : powerups) p.update(dt);
    for (auto& ex : explosions) ex.update(dt);

    waves.update(dt, enemies, static_cast<float>(game.getWindow().getSize().x));
    spawnEnemyFire(dt);
    handleCollisions();

    explosions.erase(std::remove_if(explosions.begin(), explosions.end(), [](const Explosion& e) { return e.finished(); }), explosions.end());

    auto offscreen = [h = game.getWindow().getSize().y](const Entity& e) { return e.getPosition().y < -100.f || e.getPosition().y > static_cast<float>(h) + 100.f; };
    playerBullets.erase(std::remove_if(playerBullets.begin(), playerBullets.end(), offscreen), playerBullets.end());
    enemyBullets.erase(std::remove_if(enemyBullets.begin(), enemyBullets.end(), offscreen), enemyBullets.end());
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(), offscreen), enemies.end());
    powerups.erase(std::remove_if(powerups.begin(), powerups.end(), offscreen), powerups.end());

    hud.update(score, player.health(), waveIndex);

    if (player.health() <= 0)
    {
        game.stateStack().push<GameOverState>(score, highscores);
    }
}

void GameplayState::draw(sf::RenderTarget& target)
{
    for (auto& b : playerBullets) b.draw(target);
    for (auto& b : enemyBullets) b.draw(target);
    player.draw(target);
    for (auto& e : enemies) e.draw(target);
    for (auto& p : powerups) p.draw(target);
    for (auto& ex : explosions) ex.draw(target);
    hud.draw(target);
}

void GameplayState::clampPlayerToView()
{
    auto size = game.getWindow().getSize();
    auto pos = player.getPosition();
    float halfW = player.getSize().x * 0.5f;
    float halfH = player.getSize().y * 0.5f;
    pos.x = std::clamp(pos.x, halfW, static_cast<float>(size.x) - halfW);
    pos.y = std::clamp(pos.y, halfH, static_cast<float>(size.y) - halfH);
    player.setPosition(pos);
}

void GameplayState::handleCollisions()
{
    // Player bullets vs enemies
    for (auto& b : playerBullets)
    {
        for (auto& e : enemies)
        {
            if (CollisionSystem::intersects(b, e))
            {
                e.damage(b.damage());
                b.setPosition({-1000.f, -1000.f});
                if (e.health() <= 0)
                {
                    score += 100;
                    explosions.emplace_back(e.getPosition());
                    e.setPosition({-1000.f, -1000.f});
                    if (std::rand() % 4 == 0)
                    {
                        powerups.emplace_back(PowerUpType::Heal, e.getPosition());
                    }
                }
            }
        }
    }

    // Enemy bullets vs player
    for (auto& b : enemyBullets)
    {
        if (CollisionSystem::intersects(b, player))
        {
            player.damage(1);
            b.setPosition({-1000.f, -1000.f});
        }
    }

    // Enemies vs player
    for (auto& e : enemies)
    {
        if (CollisionSystem::intersects(e, player))
        {
            player.damage(2);
            e.setPosition({-1000.f, -1000.f});
            explosions.emplace_back(e.getPosition());
        }
    }

    // Powerups vs player
    for (auto& p : powerups)
    {
        if (CollisionSystem::intersects(p, player))
        {
            switch (p.type())
            {
            case PowerUpType::Heal: player.heal(1); break;
            case PowerUpType::FireRate: player.setFireRate(0.12f); break;
            case PowerUpType::Damage: score += 50; break;
            case PowerUpType::Shield: player.heal(2); break;
            }
            p.setPosition({-1000.f, -1000.f});
        }
    }
}

void GameplayState::spawnEnemyFire(float dt)
{
    enemyFireTimer += dt;
    for (auto& e : enemies)
    {
        if (e.canFire())
        {
            e.resetFire();
            sf::Vector2f dir = player.getPosition() - e.getPosition();
            float length = std::max(1.f, std::sqrt(dir.x * dir.x + dir.y * dir.y));
            dir /= length;
            Bullet bullet(e.getPosition(), dir * 220.f, false);
            enemyBullets.push_back(bullet);
        }
    }
}
