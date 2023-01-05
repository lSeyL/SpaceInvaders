
//
// Created by seil0 on 4. 1. 2023.
//

#ifndef SPACEINVADERS_PLAYER_H
#define SPACEINVADERS_PLAYER_H

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Bullet.h"

namespace p {
class Player
{
private:
    std::string m_textureFile = "../Resources/player.png";
    sf::Texture m_texture;
    sf::Sprite m_player;
    float m_rychlostHraca;
    int m_pocetZivotov;
public:

private:

public:
    Player();  // Konštruktor
    ~Player(); // Deštruktor

    void skontrolujPoziciu(int& sirkaObrazovky, int& vyskaObrazovky);

    // Ovládanie
    void vystrel(sf::Texture& tex, std::vector<Bullet> &bullets);
    void pohybVpravo();
    void pohybVlavo();

    // Gettery
    sf::FloatRect getBounds();
    sf::Vector2f& getPosition();
    float getRychlostHraca() const;
    sf::Sprite getSprite() const;
    int getZivoty();

    // Settery
    void nastavPoziciu(int& x, int& y);
    void nastavZivoty(int pocet);


};
#endif //SPACEINVADERS_PLAYER_H

}