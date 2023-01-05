#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include "Classes/Bullet.h"
#include "Classes/Player.h"
#include "Classes/Alien.h"

const int SIRKA_OBRAZOVKY = 768;
const int VYSKA_OBRAZOVKY = 672;
const int CAS_MEDZI_STRELAMI = 650;
const float ALIEN_POSUN = 100.f;
const float ALIEN_POSUN_DOLE = 5.f;
// 4:3

bool checkCollision(sf::FloatRect rect, sf::FloatRect rect1);

void moveAliens(std::vector<sf::Sprite> spriteVector, float elapsedTime);

float zrychliPosun(float &x);


//
int main() {
    sf::RenderWindow window(sf::VideoMode(SIRKA_OBRAZOVKY, VYSKA_OBRAZOVKY), "Space Invaders");
    window.setFramerateLimit(60);
    sf::Font font;
    font.loadFromFile("../Resources/arial.ttf");

    std::string skoreString = "Skore: ";
    std::string zivotyString = "Pocet zivotov: ";
    int skoreHodnota = 0;
    sf::Text textSkore;
    textSkore.setFont(font);
    textSkore.setString(skoreString);
    textSkore.setPosition(0,0);
    textSkore.setCharacterSize(25);
    textSkore.setFillColor(sf::Color::White);
    textSkore.setStyle(sf::Text::Bold);

    sf::Text textZivoty;
    textZivoty.setFont(font);
    textZivoty.setString("3");
    textZivoty.setPosition(SIRKA_OBRAZOVKY/2,0);
    textZivoty.setCharacterSize(25);
    textZivoty.setFillColor(sf::Color::White);
    textZivoty.setStyle(sf::Text::Bold);


    sf::Texture textureAlien;
    textureAlien.loadFromFile("../Resources/alien.png");
    sf::Texture textureShot;
    textureShot.loadFromFile("../Resources/shot.png");

    p::Player hrac;
    hrac.nastavPoziciu(const_cast<int &>(SIRKA_OBRAZOVKY), const_cast<int &>(VYSKA_OBRAZOVKY));

    sf::Clock clock;
    std::chrono::time_point<std::chrono::steady_clock> lastShotTime = std::chrono::steady_clock::now();

    std::vector<Bullet> bullets;
    std::vector<Bullet> alienBullets;
    std::vector<Alien> enemies;
    int enemyDirection = 1;
    bool reachedPlayer = false;

    int pocetRad = 10;
    int pocetStlpec = 3;
    for (int i = 0; i < pocetRad; ++i) {
        for (int j = 0; j < pocetStlpec; ++j) {
            //Sirka ikonky je 51px
            //10 je medzera
            //768 - 510 = 258, 258 - 10 * 10 = 158 / 2 = 79
            int offsetX = 79;
            int offsetY = 50;
            int medzera = 10;
            Alien alien;
            alien.setPosition(offsetX, offsetY, medzera, i, j);
            enemies.push_back(alien);
        }
    }

    while (window.isOpen()) {
        sf::Event event{};

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        float elapsedTime = clock.restart().asSeconds();
        auto currentTime = std::chrono::steady_clock::now();

        //Ovladanie
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            hrac.skontrolujPoziciu(const_cast<int &>(SIRKA_OBRAZOVKY), const_cast<int &>(VYSKA_OBRAZOVKY));
            hrac.pohybVlavo();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            hrac.skontrolujPoziciu(const_cast<int &>(SIRKA_OBRAZOVKY), const_cast<int &>(VYSKA_OBRAZOVKY));
            hrac.pohybVpravo();
        }

        if (currentTime - lastShotTime > std::chrono::milliseconds(CAS_MEDZI_STRELAMI)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                hrac.vystrel(textureShot, bullets);
                lastShotTime = currentTime;
            }
        }


        for (auto &bullet: bullets) {
            bullet.move(0.0f, -1000.0f * elapsedTime);

        }

        for (auto &bullet: alienBullets) {
            bullet.move(0.0f, 500.0f * elapsedTime);

        }

        // Remove bullets that have gone off the screen
        bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [&](const auto &bullet) {
            return bullet.getPosition().y < 0;
        }), bullets.end());

        alienBullets.erase(std::remove_if(alienBullets.begin(), alienBullets.end(), [&](const auto &bullet) {
            return bullet.getPosition().y < 0;
        }), alienBullets.end());
        //

        for (auto &bullet: bullets) {
            for (int i = 0; i < enemies.size(); i++) {
                if (checkCollision(bullet.getSprite().getGlobalBounds(), enemies[i].getGlobalBounds())) {
                    Alien hitAlien = enemies[i];
                    enemies.erase(enemies.begin() + i);
                    bullet = bullets.back();
                    bullets.pop_back();
                    skoreString = "Skore: ";
                    skoreHodnota += 300;
                    skoreString += std::to_string(skoreHodnota);
                }

            }
        }

        for (auto &bullet: alienBullets) {
            for (int i = 0; i < enemies.size(); i++) {
                if (checkCollision(bullet.getSprite().getGlobalBounds(), hrac.getSprite().getGlobalBounds())) {
                    int pocetZivotov = hrac.getZivoty();
                    hrac.nastavZivoty(pocetZivotov - 1);
                    bullet = alienBullets.back();
                    alienBullets.pop_back();
                    std::cout << "Hit " << pocetZivotov << "\n";

                }

            }
        }

        window.clear();
        window.draw(hrac.getSprite());

        for (Alien &alien: enemies) {
            alien.pohyb(ALIEN_POSUN * enemyDirection * elapsedTime, 0.0f);

        }


        for (Alien &alien: enemies) {
            alien.vystrel(textureShot, alienBullets);

        }


        for (Alien &alien: enemies) {
            bool aliensMoveDown = false;
            if (alien.getPosition().x < 0) {
                enemyDirection = 1;
                aliensMoveDown = true;
            }
            if (alien.getPosition().x > SIRKA_OBRAZOVKY - alien.getLocalBounds().width) {
                enemyDirection = -1;
                aliensMoveDown = true;
            }
            if (aliensMoveDown) {
                for (Alien &aaalien: enemies) {
                    aaalien.pohyb(0.0f, ALIEN_POSUN_DOLE);
                }
                aliensMoveDown = false;
                std::cout << "Pos " << enemies[1].getPosition().y << "\n";
            }

        }


        for (Alien &alien: enemies) {
            window.draw(alien.getSprite());
        }
        for (Bullet &bullet: bullets) {
            window.draw(bullet.getSprite());
        }
        for (Bullet &bullet: alienBullets) {
            window.draw(bullet.getSprite());
        }

        //Koniec hry
        if (enemies.empty()) {
            std::cout << "Vyhra!";
            bullets.clear();
            enemies.clear();
            return 0;
        }
        for(Alien& alien : enemies)
        {
            if(alien.getPosition().y > VYSKA_OBRAZOVKY)
            {
                reachedPlayer = true;
                std::cout << "Prehra\n";
                std::cout << "Nepriatelia dosli na koniec obrazovky.\n";
                return 1;
            }
        }

        if (hrac.getZivoty() <= 0) {
            std::cout << "Prehra\n";
            std::cout << "Stratil si vsetky zivoty.\n";
            return 1;
        }

        zivotyString = "Pocet zivotov: ";
        zivotyString += std::to_string(hrac.getZivoty());
        textZivoty.setString(zivotyString);
        textSkore.setString(skoreString);
        window.draw(textSkore);
        window.draw(textZivoty);
        window.display();
    }


}


void moveAliens(std::vector<sf::Sprite> spriteVector, float elapsedTime) {
    for (int i = 0; i < spriteVector.size(); ++i) {
        spriteVector[i].move(100.0f * 1 * elapsedTime, 0.0f);
    }
}


bool checkCollision(sf::FloatRect box1, sf::FloatRect box2) {
    return box1.left < box2.left + box2.width && box1.left + box1.width > box2.left &&
           box1.top < box2.top + box2.height && box1.top + box1.height > box2.top;
}

float zrychliPosun(float &x) {
    return x *= 2;
}





