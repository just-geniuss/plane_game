#pragma once

#include <SFML/Graphics.hpp>

class HUD
{
public:
    HUD();

    void setFont(const sf::Font* font);
    void update(int score, int hp, int wave);
    void draw(sf::RenderTarget& target) const;

private:
    sf::Text scoreText;
    sf::Text hpText;
    sf::Text waveText;
};
