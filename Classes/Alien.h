

//
// Created by seil0 on 4. 1. 2023.
//

#ifndef SPACEINVADERS_ALIEN_H
#define SPACEINVADERS_ALIEN_H

#include <SFML/Graphics.hpp>
#include <string>
#include <cstdlib>
#include <iostream>
#include "Bullet.h"

class Alien{
private:
    std::string textureAlienFile = "../Resources/alien.png";
    sf::Sprite alien;
    sf::Texture textureAlien;
public:
    Alien();
    //Alien(sf::Texture& tex);
    ~Alien();
    sf::Sprite getAlienSprite() {return alien;};
    sf::Texture getAlien() {return textureAlien;};
    //std::vector<sf::Sprite> getEnemiesZoznam() {return enemies;};
    //void zmazNepriatela(std::vector<Bullet> bullets, std::vector<Sprite> enemies, bool checkCollision(sf::FloatRect rect, sf::FloatRect rect1));
    void setPosition(int X, int Y, int medzera, int i, int j);
    //void setEnemiesVector(std::vector<Alien> *enemy);
    void createEnemySprite();
    void pohyb(float offsetX, float offsetY);
    sf::Sprite getSprite() const;
    sf::FloatRect getGlobalBounds();
    sf::FloatRect getLocalBounds();
    sf::Vector2f& getPosition();
    void vystrel(sf::Texture& tex, std::vector<Bullet> &alienBullets);

    Alien(sf::Sprite sprite);
};


#endif //SPACEINVADERS_ALIEN_H
