

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
    std::string m_textureAlienFile;
    sf::Sprite m_alienSp;
    sf::Texture m_textureAlien;
    bool m_alive;
    int m_hp;
public:
    Alien();
    explicit Alien(sf::Texture& tex);
    ~Alien();
    sf::Sprite getAlienSprite() {return m_alienSp;};
    sf::Texture getAlienTexture() {return m_textureAlien;};
    //std::vector<sf::Sprite> getEnemiesZoznam() {return enemies;};
    //void zmazNepriatela(std::vector<Bullet> bullets, std::vector<Sprite> enemies, bool checkCollision(sf::FloatRect rect, sf::FloatRect rect1));
    void setPosition(int X, int Y, int medzera, int i, int j);
    //void setEnemiesVector(std::vector<Alien> *enemy);
    void createTex();
    void pohyb(float offsetX, float offsetY);
    sf::Sprite getSprite() const;
    sf::FloatRect getGlobalBounds();
    sf::FloatRect getLocalBounds();
    sf::Vector2f& getPosition();
    void vystrel(sf::Texture& tex, std::vector<Bullet> &alienBullets);
    bool isAlive();
    void setAliveState(bool setLive);
    void setScale(float x, float y);


};


#endif //SPACEINVADERS_ALIEN_H
