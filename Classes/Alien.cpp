//
// Created by adria on 4. 1. 2023.
//

#include "Alien.h"


Alien::Alien() {
}

Alien::Alien(sf::Texture &tex) {
    m_alienSp.setTexture(tex);
    m_alive = true;
}

Alien::~Alien() {

}

/*
void Alien::zmazNepriatela(std::vector<Bullet> bullets, std::vector<Sprite> enemies, bool checkCollision(sf::FloatRect rect, sf::FloatRect rect1)) {

    for (auto &bullet: bullets) {
        for (int i = 0; i < enemies.size(); i++) {
            if (checkCollision(bullet.getSprite().getGlobalBounds(), enemies[i].getGlobalBounds())) {
                sf::Sprite hitAlien = enemies[i];
                enemies.erase(enemies.begin() + i);
                bullet = bullets.back();
                bullets.pop_back();
            }

        }
    }

}
 */

void Alien::setPosition(int X, int Y, int medzera, int i, int j) {
    m_alienSp.setPosition(X + (m_alienSp.getLocalBounds().width + medzera) * i,
                      Y + (m_alienSp.getLocalBounds().height + medzera) * j);
}

/*
void Alien::setEnemiesVector(std::vector<Alien> *enemy) {
    enemy->push_back(this->alien);
}
 */

void Alien::createTex() {
    m_textureAlien.loadFromFile(m_textureAlienFile);
    m_alienSp.setTexture(m_textureAlien);
}

sf::Sprite Alien::getSprite() const {
    return this->m_alienSp;
}

sf::FloatRect Alien::getGlobalBounds() {
    return this->m_alienSp.getGlobalBounds();
}

sf::Vector2f &Alien::getPosition() {
    return const_cast<sf::Vector2f &>(this->m_alienSp.getPosition());
}

void Alien::pohyb(float offsetX, float offsetY) {
    this->m_alienSp.move(offsetX, offsetY);
}

sf::FloatRect Alien::getLocalBounds() {
    return this->m_alienSp.getLocalBounds();
}

void Alien::vystrel(sf::Texture &tex, std::vector<Bullet> &alienBullets) {
    Bullet bullet(tex);
    bullet.setPosition(this->m_alienSp.getPosition().x + 25, this->m_alienSp.getPosition().y + 25);
    alienBullets.push_back(bullet);

}

bool Alien::isAlive() {
    return this->m_alive;
}

void Alien::setAliveState(bool setLive) {
    this->m_alive = setLive;
}

void Alien::setScale(float x, float y) {
    this->m_alienSp.setScale(x,y);
}











