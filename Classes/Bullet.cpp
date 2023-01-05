//
// Created by seil0 on 4. 1. 2023.
//

#include "Bullet.h"

Bullet::Bullet(const sf::Texture& texture) : sprite(texture) {}

void Bullet::setPosition(float x, float y) {
  sprite.setPosition(x, y);
}

sf::Vector2f Bullet::getPosition() const {
  return sprite.getPosition();
}

sf::Sprite Bullet::getSprite() const {
  return sprite;
}

void Bullet::move(float x, float y) {
  sprite.move(x, y);
}

Bullet Bullet::getBullet() const{
    return *this;
}