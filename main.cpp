#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <chrono>
#include <iostream>
#include "Classes/Bullet.h"
#include "Classes/Player.h"
#include "Classes/Alien.h"
#include "Classes/AlienArmy.h"


// 4:3
const int SIRKA_OBRAZOVKY = 768;
const int VYSKA_OBRAZOVKY = 672;

const int CAS_MEDZI_STRELAMI = 750;

const float ALIEN_POSUN = 250.f;
const float ALIEN_POSUN_DOLE = 6.f;

float zrychlenie = 0.1f;


bool checkCollision(sf::FloatRect rect, sf::FloatRect rect1);

void moveAliens(std::vector<sf::Sprite> spriteVector, float elapsedTime);

float zrychliPosun(float &x);


//
int main() {
    //

    sf::Mutex mutex;
    int player;
    std::cout << "Player(0) or player(1). " << std::endl;
    std::cout << "Player0 uses Arrows to move and Spacebar to shoot,  " << std::endl;
    std::cout << "Player1 uses A,D to move and LControl to shoot." << std::endl;
    std::cin >> player;
    bool reachedPlayer = false;

    sf::IpAddress ipAddress = sf::IpAddress::getLocalAddress();
    sf::TcpSocket socket;
    char buffer[1024];
    char connectionType;
    int pocetHracov = 0;


    std::cout << "Type (s) to make a server, or (c) to connect to the server. " << std::endl;
    std::cout << "If there is no server running, you will start a solo session. " << std::endl;
    std::cin >> connectionType;

    if (connectionType == 's') {
        sf::TcpListener listener;
        listener.listen(51000);
        listener.accept(socket);
        std::cout << "Making a server.. " << std::endl;
        pocetHracov++;
    } else if (connectionType == 'c') {
        socket.connect(ipAddress, 51000);
        std::cout << "New client connected: " << socket.getRemoteAddress() << std::endl;
        pocetHracov++;

    } else {
        std::cerr << "Error connection type" << std::endl;
        std::cin >> connectionType;
        return 1;
    }


    //
    sf::RenderWindow window(sf::VideoMode(SIRKA_OBRAZOVKY, VYSKA_OBRAZOVKY), "Space Invaders");
    window.setFramerateLimit(60);
    auto image = sf::Image{};
    if (!image.loadFromFile("../Resources/alien.png")) {
        // Error handling...
    }
    window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());


    //
    sf::Font font;
    font.loadFromFile("../Resources/arial.ttf");

    std::string skoreString = "Skore: 0";
    std::string zivotyString = "Pocet zivotov: ";
    std::string pocetEnemiesString = "Enemies: ";
    int skoreHodnota = 0;
    sf::Text textSkore;
    textSkore.setFont(font);
    textSkore.setString(skoreString);
    textSkore.setPosition(0, 0);
    textSkore.setCharacterSize(25);
    textSkore.setFillColor(sf::Color::White);
    textSkore.setStyle(sf::Text::Bold);

    sf::Text textZivoty;
    textZivoty.setFont(font);
    textZivoty.setString(zivotyString);
    textZivoty.setPosition(SIRKA_OBRAZOVKY / 3, 0);
    textZivoty.setCharacterSize(25);
    textZivoty.setFillColor(sf::Color::White);
    textZivoty.setStyle(sf::Text::Bold);

    sf::Text textNumOfEnemies;
    textNumOfEnemies.setFont(font);
    textNumOfEnemies.setString(pocetEnemiesString);
    textNumOfEnemies.setPosition(SIRKA_OBRAZOVKY / 4 + SIRKA_OBRAZOVKY / 2, 0);
    textNumOfEnemies.setCharacterSize(25);
    textNumOfEnemies.setFillColor(sf::Color::White);
    textNumOfEnemies.setStyle(sf::Text::Bold);


    sf::Texture texBackground;
    texBackground.loadFromFile("../Resources/bg.png");
    sf::Sprite background;
    background.setTexture(texBackground);
    background.setPosition(0, 0);


    sf::Texture textureAlien;
    textureAlien.loadFromFile("../Resources/alien.png");

    sf::Texture textureAlien2;
    textureAlien2.loadFromFile("../Resources/alien2.png");

    sf::Texture textureAlien3;
    textureAlien3.loadFromFile("../Resources/alien3.png");


    sf::Texture textureAlienShot;
    textureAlienShot.loadFromFile("../Resources/shotAlien.png");
    sf::Texture textureShot;
    textureShot.loadFromFile("../Resources/shot.png");
    std::vector<p::Player> players;

    sf::Texture texturePlayerOne;
    texturePlayerOne.loadFromFile("../Resources/p1.png");

    sf::Texture texturePlayerTwo;
    texturePlayerTwo.loadFromFile("../Resources/p2.png");


    p::Player hrac(texturePlayerOne);
    p::Player druhyHrac(texturePlayerTwo);

    hrac.setPlayer(true);
    druhyHrac.setPlayer(false);

    hrac.nastavStartovnuPoziciu(const_cast<int &>(SIRKA_OBRAZOVKY), const_cast<int &>(VYSKA_OBRAZOVKY));
    druhyHrac.nastavStartovnuPoziciu(const_cast<int &>(SIRKA_OBRAZOVKY), const_cast<int &>(VYSKA_OBRAZOVKY));


    sf::Clock clock;
    std::chrono::time_point<std::chrono::steady_clock> lastShotTime = std::chrono::steady_clock::now();

    std::vector<Bullet> bullets;
    std::vector<Bullet> alienBullets;
    std::vector<Alien> enemies;


    int enemyDirection = 1;

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
            if (j == 0) {
                Alien alien(textureAlien3);
                alien.setPosition(offsetX, offsetY, medzera, i, j);
                enemies.push_back(alien);
            } else if (j == 1) {
                Alien alien(textureAlien2);
                alien.setPosition(offsetX, offsetY, medzera, i, j);
                enemies.push_back(alien);
            } else {
                Alien alien(textureAlien);
                alien.setPosition(offsetX, offsetY, medzera, i, j);
                enemies.push_back(alien);
            }


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
        if (player == 0) {
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
        } else if (player == 1) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                hrac.skontrolujPoziciu(const_cast<int &>(SIRKA_OBRAZOVKY), const_cast<int &>(VYSKA_OBRAZOVKY));
                hrac.pohybVlavo();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                hrac.skontrolujPoziciu(const_cast<int &>(SIRKA_OBRAZOVKY), const_cast<int &>(VYSKA_OBRAZOVKY));
                hrac.pohybVpravo();
            }

            if (currentTime - lastShotTime > std::chrono::milliseconds(CAS_MEDZI_STRELAMI)) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                    hrac.vystrel(textureShot, bullets);
                    lastShotTime = currentTime;
                }
            }
        } else {
            std::cerr << "Error! Failed to select player controls." << std::endl;
            std::cout << "Error! Failed to select player controls." << std::endl;
        }


        for (auto &bullet: bullets) {
            bullet.move(0.0f, -1000.0f * elapsedTime);
        }

        for (auto &bullet: alienBullets) {
            bullet.move(0.0f, 100.0f * elapsedTime);
        }

        //
        bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [&](const auto &bullet) {
            return bullet.getPosition().y < 0;
        }), bullets.end());

        alienBullets.erase(std::remove_if(alienBullets.begin(), alienBullets.end(), [&](const auto &bullet) {
            return bullet.getPosition().y < 0;
        }), alienBullets.end());
        //
        sf::Packet packet;
        sf::Packet packetPlayerPos;
        sf::Packet packetAlienShooting;

        bool enemyHit = false;

        for (auto &bullet: bullets) {
            for (int i = 0; i < enemies.size(); i++) {
                if (checkCollision(bullet.getSprite().getGlobalBounds(), enemies[i].getGlobalBounds())) {
                    int posHitEnemy = 0;
                    posHitEnemy = i;
                    Alien hitAlien = enemies[i];
                    hitAlien.setAliveState(false);
                    enemies[i].setAliveState(false);

                    bullet = bullets.back();
                    bullets.pop_back();

                    skoreHodnota += 300;
                    skoreString = "Skore: ";
                    skoreString += std::to_string(skoreHodnota);
                    enemyHit = true;
                    int numberOfEnemies = 0;
                    numberOfEnemies = enemies.size();
                    packet << numberOfEnemies << posHitEnemy << enemyHit;


                }

            }
        }

        for (Alien &alien: enemies) {
            alien.pohyb(ALIEN_POSUN * enemyDirection * elapsedTime * zrychlenie, 0.0f);
        }



        /*

        bool boolChanceShooting = false;
        int posChance = 0;
        for (int i = 0; i < enemies.size(); ++i) {
            if ((rand() % 1000) < 1) {
                boolChanceShooting = true;
                posChance = i;
                packetAlienShooting << posChance << boolChanceShooting;
            }

        }
        */


        for(Alien& alien: enemies)
        {
            if ((rand() % 1000) < 1) {
                alien.vystrel(textureAlienShot, alienBullets);
            }
        }



        float posX;
        posX = hrac.getPosition().x;
        float posY;
        posY = hrac.getPosition().y;

        packetPlayerPos << posX << posY;

        mutex.lock();
        //
        socket.send(packet);
        socket.send(packetPlayerPos);
        socket.send(packetAlienShooting);
        //
        mutex.unlock();

        mutex.lock();
        //
        socket.receive(packet);
        socket.receive(packetPlayerPos);
        socket.receive(packetAlienShooting);
        //
        mutex.unlock();

        int pos;
        unsigned int pocetEnem = enemies.size();
        bool hit;
        packet >> pocetEnem >> pos >> hit;

        packetPlayerPos >> posX >> posY;
        druhyHrac.nastavPozicu(posX, posY);

        if (hit) {
            //int posHitEnemy;
            enemies.erase(enemies.begin() + pos);
            hit = false;
        }
        for (int i = 0; i < enemies.size(); ++i) {
            if (!enemies[i].isAlive()) {
                enemies.erase(enemies.begin() + i);
            }
        }



    /*
        int alienShooting;
        bool chance;
        for (int i = 0; i < enemies.size(); ++i) {
            packetAlienShooting >> alienShooting >> chance;
            if (chance) {
                enemies[alienShooting].vystrel(textureAlienShot, alienBullets);
                chance = false;
            }
        }

    */

        for (auto &bullet: alienBullets) {
            for (int i = 0; i < enemies.size(); i++) {
                if (checkCollision(bullet.getSprite().getGlobalBounds(), hrac.getSprite().getGlobalBounds())) {
                    int pocetZivotov = hrac.getZivoty();
                    hrac.nastavZivoty(pocetZivotov - 1);
                    bullet = alienBullets.back();
                    alienBullets.pop_back();
                }
            }
        }
        //
        window.clear();
        window.draw(background);

        window.draw(hrac.getSprite());
        window.draw(druhyHrac.getSprite());


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
                zrychlenie += 0.02f;
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
            alienBullets.clear();
            enemies.clear();

            return 0;
        }
        for (Alien &alien: enemies) {
            if (alien.getPosition().y > VYSKA_OBRAZOVKY) {
                reachedPlayer = true;
                bullets.clear();
                alienBullets.clear();

                enemies.clear();
                std::cout << "Prehra\n";
                std::cout << "Nepriatelia dosli na koniec obrazovky.\n";
                return 1;
            }
        }

        if (hrac.getZivoty() <= 0) {
            std::cout << "Prehra\n";
            std::cout << "Stratil si vsetky zivoty.\n";
            bullets.clear();
            alienBullets.clear();
            //deadEnemies.clear();
            enemies.clear();
            return 1;
        }




        //packetKilledPosition >> posHitEnemy;


        zivotyString = "Pocet zivotov: ";
        zivotyString += std::to_string(hrac.getZivoty());
        pocetEnemiesString = "Enemies: ";
        pocetEnemiesString += std::to_string(pocetEnem);
        textZivoty.setString(zivotyString);
        textSkore.setString(skoreString);
        textNumOfEnemies.setString(pocetEnemiesString);
        window.draw(textNumOfEnemies);
        window.draw(textSkore);
        window.draw(textZivoty);

        window.draw(druhyHrac.getSprite());
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





