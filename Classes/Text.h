//
// Created by Richen on 6.1.2023.
//

//Header ku triede Text.cpp

#ifndef SPACEINVADERS_TEXT_H
#define SPACEINVADERS_TEXT_H

#pragma once

#include <SFML/Graphics.hpp>

class Text
{
public:
    Text(const std::string& str, const sf::Font& font, unsigned int characterSize, sf::Color color, bool bold);

    void setString(const std::string& str);
    void setPosition(float x, float y);
    void setCharacterSize(unsigned int size);
    void setFillColor(const sf::Color& color);
    void setStyle(sf::Text::Style style);

    const sf::Text& getSFMLText() const;

private:
    sf::Text m_text;

};






#endif //SPACEINVADERS_TEXT_H
