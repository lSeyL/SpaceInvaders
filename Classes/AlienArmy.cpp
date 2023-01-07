//
// Created by seil0 on 6. 1. 2023.
//

#include "AlienArmy.h"

AlienArmy::AlienArmy() {

}

AlienArmy::~AlienArmy() {

}

void AlienArmy::vytvorArmadu(int rad, int stlpec, std::vector<Alien> enemies, sf::Texture& t1, sf::Texture& t2, sf::Texture& t3) {
    int pocetRad = rad;
    int pocetStlpec = stlpec;

    for (int i = 0; i < pocetRad; ++i) {
        for (int j = 0; j < pocetStlpec; ++j) {
            //Sirka ikonky je 51px
            //10 je medzera
            //768 - 510 = 258, 258 - 10 * 10 = 158 / 2 = 79
            int offsetX = 79;
            int offsetY = 50;
            int medzera = 10;
            if (j == 0) {
                Alien alien(t3);
                alien.setPosition(offsetX, offsetY, medzera, i, j);
                enemies.push_back(alien);
            } else if (j == 1) {
                Alien alien(t2);
                alien.setPosition(offsetX, offsetY, medzera, i, j);
                enemies.push_back(alien);
            } else {
                Alien alien(t1);
                alien.setPosition(offsetX, offsetY, medzera, i, j);
                enemies.push_back(alien);
            }


        }
    }
}
