//
// Created by adria on 4. 1. 2023.
//

#include "Alien.h"


Alien::Alien() : textureAlienFile("../Resources/alien.png") {
    textureAlien.loadFromFile(textureAlienFile);
    alien.setTexture(textureAlien);
}
/*
Alien::Alien(sf::Texture& tex) {
    tex.loadFromFile(textureAlienFile);
    alien.setTexture(tex);
}
 */
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
    alien.setPosition(X + (alien.getLocalBounds().width + medzera) * i,
                      Y  + (alien.getLocalBounds().height + medzera) * j);
}

/*
void Alien::setEnemiesVector(std::vector<Alien> *enemy) {
    enemy->push_back(this->alien);
}
 */

void Alien::createEnemySprite() {
    textureAlien.loadFromFile(textureAlienFile);
    alien.setTexture(textureAlien);
}

sf::Sprite Alien::getSprite() const {
    return this->alien;
}

sf::FloatRect Alien::getGlobalBounds() {
    return this->alien.getGlobalBounds();
}

sf::Vector2f &Alien::getPosition() {
    return const_cast<sf::Vector2f &>(this->alien.getPosition());
}

void Alien::pohyb(float offsetX, float offsetY) {
    this->alien.move(offsetX,offsetY);
}

sf::FloatRect Alien::getLocalBounds() {
    return this->alien.getLocalBounds();
}

void Alien::vystrel(sf::Texture& tex, std::vector<Bullet> &alienBullets) {
    if( (rand() % 1000) < 1)
    {
        Bullet bullet(tex);
        bullet.setPosition(this->alien.getPosition().x, this->alien.getPosition().y);
        alienBullets.push_back(bullet);
    }
}









