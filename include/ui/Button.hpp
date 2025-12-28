#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <string>

class Button
{
public:
    Button();
    void setText(const std::string& text, const sf::Font* font, unsigned int size = 24);
    void setPosition(const sf::Vector2f& pos);
    void setCallback(std::function<void()> cb);

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
    void draw(sf::RenderTarget& target) const;

    void setSize(const sf::Vector2f& s);

private:
    sf::RectangleShape box;
    sf::Text label;
    std::function<void()> callback;
};
