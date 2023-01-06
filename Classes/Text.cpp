//
// Created by Richen on 6.1.2023.
//

#include "Text.h"

Text::Text(const sf::Font& font, unsigned int characterSize, sf::Color color, bool bold)
{
    m_text.setFont(font);
    m_text.setCharacterSize(characterSize);
    m_text.setFillColor(color);
    m_text.setStyle(bold ? sf::Text::Bold : sf::Text::Regular);
}

void Text::setString(const std::string& str)
{
    m_text.setString(str);
}

void Text::setPosition(float x, float y)
{
    m_text.setPosition(x, y);
}

void Text::setCharacterSize(unsigned int size)
{
    m_text.setCharacterSize(size);
}

void Text::setFillColor(const sf::Color& color)
{
    m_text.setFillColor(color);
}

void Text::setStyle(sf::Text::Style style)
{
    m_text.setStyle(style);
}

const sf::Text& Text::getSFMLText() const
{
    return m_text;
}


