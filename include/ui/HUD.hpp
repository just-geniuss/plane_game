#pragma once

#include <SFML/Graphics.hpp>
#include <optional>

class HUD
{
public:
    HUD();

    void setFont(const sf::Font* font);
    void update(int score, int hp, int wave);
    void draw(sf::RenderTarget& target) const;

private:
#if SFML_VERSION_MAJOR >= 3
    std::optional<sf::Text> scoreText;
    std::optional<sf::Text> hpText;
    std::optional<sf::Text> waveText;
#else
    sf::Text scoreText;
    sf::Text hpText;
    sf::Text waveText;
#endif
};
