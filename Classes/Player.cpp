//
// Created by seil0 on 4. 1. 2023.
//

#include "Player.h"


p::Player::Player() {
    m_texture.loadFromFile(m_textureFile);
    m_player.setTexture(m_texture);
    this->m_rychlostHraca = 3.5f;
    this->m_pocetZivotov = 3;
    this->playerOne = false;
}

p::Player::~Player() {

}

void p::Player::pohybVpravo() {
    this->m_player.move(getRychlostHraca() * 1, 0);
}

void p::Player::pohybVlavo() {
    this->m_player.move(getRychlostHraca() * -1, 0);
}

void p::Player::vystrel(sf::Texture& tex, std::vector<Bullet> &bullets) {
    Bullet bullet(tex);
    bullet.setPosition(getSprite().getPosition().x + 21, getSprite().getPosition().y);
    bullets.push_back(bullet);
}


sf::Sprite p::Player::getSprite() const {
    return this->m_player;
}



float p::Player::getRychlostHraca() const {
    return this->m_rychlostHraca;
}

void p::Player::nastavPoziciu(int& sirkaObrazovky, int& vyskaObrazovky) {
    this->m_player.setPosition(sirkaObrazovky / 2 - 25, vyskaObrazovky - this->m_player.getLocalBounds().height);
}

sf::FloatRect p::Player::getBounds() {
    return this->m_player.getLocalBounds();
}

sf::Vector2f &p::Player::getPosition() {
    return const_cast<sf::Vector2f &>(this->m_player.getPosition());
}

int p::Player::getZivoty(){
    return this->m_pocetZivotov;
}

void p::Player::nastavZivoty(int pocet) {
    this->m_pocetZivotov = pocet;
}

void p::Player::skontrolujPoziciu(int& sirkaObrazovky, int& vyskaObrazovky) {
    if (this->m_player.getPosition().x > sirkaObrazovky - this->m_player.getLocalBounds().width) {
        this->m_player.setPosition(sirkaObrazovky - this->m_player.getLocalBounds().width, this->m_player.getPosition().y);
    }
    if (this->m_player.getPosition().x < 0) {
        this->m_player.setPosition(0, this->m_player.getPosition().y);
    }

}

void p::Player::setPlayer(bool playerNum) {
    this->playerOne = playerNum;
}

bool p::Player::isPlayerOne() {
    return  this->playerOne;
}









