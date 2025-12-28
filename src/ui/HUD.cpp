#include "ui/HUD.hpp"

HUD::HUD()
{
#if SFML_VERSION_MAJOR < 3
    scoreText.setPosition(20.f, 20.f);
    hpText.setPosition(20.f, 50.f);
    waveText.setPosition(20.f, 80.f);
#endif
}

void HUD::setFont(const sf::Font* font)
{
    if (font)
    {
        #if SFML_VERSION_MAJOR >= 3
        scoreText.emplace(*font, "", 18);
        hpText.emplace(*font, "", 18);
        waveText.emplace(*font, "", 18);
        scoreText->setPosition(20.f, 20.f);
        hpText->setPosition(20.f, 50.f);
        waveText->setPosition(20.f, 80.f);
        #else
        scoreText.setFont(*font);
        hpText.setFont(*font);
        waveText.setFont(*font);
        scoreText.setCharacterSize(18);
        hpText.setCharacterSize(18);
        waveText.setCharacterSize(18);
        #endif
    }
}

void HUD::update(int score, int hp, int wave)
{
#if SFML_VERSION_MAJOR >= 3
    if (scoreText) scoreText->setString("Score: " + std::to_string(score));
    if (hpText) hpText->setString("HP: " + std::to_string(hp));
    if (waveText) waveText->setString("Wave: " + std::to_string(wave));
#else
    scoreText.setString("Score: " + std::to_string(score));
    hpText.setString("HP: " + std::to_string(hp));
    waveText.setString("Wave: " + std::to_string(wave));
#endif
}

void HUD::draw(sf::RenderTarget& target) const
{
#if SFML_VERSION_MAJOR >= 3
    if (scoreText)
        target.draw(*scoreText);
    if (hpText)
        target.draw(*hpText);
    if (waveText)
        target.draw(*waveText);
#else
    if (scoreText.getFont())
        target.draw(scoreText);
    if (hpText.getFont())
        target.draw(hpText);
    if (waveText.getFont())
        target.draw(waveText);
#endif
}
