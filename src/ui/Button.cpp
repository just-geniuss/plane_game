#include "ui/Button.hpp"

#include <variant>

Button::Button()
{
    box.setSize({220.f, 44.f});
    box.setFillColor(sf::Color(40, 60, 90));
    box.setOutlineThickness(2.f);
    box.setOutlineColor(sf::Color(120, 160, 220));
}

void Button::setText(const std::string& text, const sf::Font* font, unsigned int size)
{
#if SFML_VERSION_MAJOR >= 3
    if (font)
    {
        label.emplace(*font, text, size);
        label->setFillColor(sf::Color::White);
        auto bounds = label->getLocalBounds();
        label->setOrigin({bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f});
        label->setPosition(box.getPosition());
    }
    else
    {
        label.reset();
    }
#else
    if (font)
    {
        label.setFont(*font);
    }
    label.setString(text);
    label.setCharacterSize(size);
    label.setFillColor(sf::Color::White);
    auto bounds = label.getLocalBounds();
    label.setOrigin({bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f});
    label.setPosition(box.getPosition());
#endif
}

void Button::setPosition(const sf::Vector2f& pos)
{
    box.setPosition(pos);
#if SFML_VERSION_MAJOR >= 3
    if (label)
        label->setPosition(pos);
#else
    label.setPosition(pos);
#endif
}

void Button::setCallback(std::function<void()> cb)
{
    callback = std::move(cb);
}

void Button::handleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
    #if SFML_VERSION_MAJOR >= 3
        if (const auto* mb = event.getIf<sf::Event::MouseButtonReleased>())
        {
            if (mb->button == sf::Mouse::Button::Left)
            {
                auto mouse = sf::Vector2f(sf::Mouse::getPosition(window));
                if (box.getGlobalBounds().contains(mouse))
                {
                    if (callback)
                        callback();
                }
            }
        }
        #else
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    {
        auto mouse = sf::Vector2f(sf::Mouse::getPosition(window));
        if (box.getGlobalBounds().contains(mouse))
        {
            if (callback)
                callback();
        }
    }
    #endif
}

void Button::draw(sf::RenderTarget& target) const
{
    target.draw(box);
#if SFML_VERSION_MAJOR >= 3
    if (label)
        target.draw(*label);
#else
    if (label.getFont())
        target.draw(label);
#endif
}

void Button::setSize(const sf::Vector2f& s)
{
    box.setSize(s);
    box.setOrigin(s * 0.5f);
}
