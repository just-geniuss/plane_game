#include "ui/HUD.hpp"

HUD::HUD()
{
    scoreText.setPosition(20.f, 20.f);
    hpText.setPosition(20.f, 50.f);
    waveText.setPosition(20.f, 80.f);
}

void HUD::setFont(const sf::Font* font)
{
    if (font)
    {
        scoreText.setFont(*font);
        hpText.setFont(*font);
        waveText.setFont(*font);
    }
    scoreText.setCharacterSize(18);
    hpText.setCharacterSize(18);
    waveText.setCharacterSize(18);
}

void HUD::update(int score, int hp, int wave)
{
    scoreText.setString("Score: " + std::to_string(score));
    hpText.setString("HP: " + std::to_string(hp));
    waveText.setString("Wave: " + std::to_string(wave));
}

void HUD::draw(sf::RenderTarget& target) const
{
    if (scoreText.getFont())
        target.draw(scoreText);
    if (hpText.getFont())
        target.draw(hpText);
    if (waveText.getFont())
        target.draw(waveText);
}
