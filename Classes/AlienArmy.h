//
// Created by seil0 on 6. 1. 2023.
//

#ifndef SPACEINVADERS_ALIENARMY_H
#define SPACEINVADERS_ALIENARMY_H


#include <vector>
#include "Alien.h"

class AlienArmy {
private:

public:
    AlienArmy();
    ~AlienArmy();
    void vytvorArmadu(int rad, int stlpec, std::vector<Alien>& enemies, sf::Texture& t1, sf::Texture& t2, sf::Texture& t3);

private:

public:
};


#endif //SPACEINVADERS_ALIENARMY_H
