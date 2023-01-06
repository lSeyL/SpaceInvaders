//
// Created by Richen7 on 4. 1. 2023.
//
#ifndef SPACEINVADERS_BULLET_H
#define SPACEINVADERS_BULLET_H
#pragma once

#include <SFML/Graphics.hpp>

class Bullet : public sf::Sprite{
public:
  Bullet(const sf::Texture& texture);

  void setPosition(float x, float y);
  sf::Vector2f getPosition() const;
  sf::Sprite getSprite() const;
  void move(float x, float y);
  Bullet getBullet() const;

private:
  sf::Sprite sprite;
};

#endif //SPACEINVADERS_BULLET_H
