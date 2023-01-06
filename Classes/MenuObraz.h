//
// Created by adria on 6. 1. 2023.
//

#ifndef SPACEINVADERS_MENUOBRAZ_H
#define SPACEINVADERS_MENUOBRAZ_H
#include <SFML/Graphics.hpp>
#include "Menu.h"

class MenuObraz {
public:
    MenuObraz();
    void zobrazMenu();
    virtual ~MenuObraz();

private:
    const int SIRKA_OBRAZOVKY = 768;
    const int VYSKA_OBRAZOVKY = 672;
};


#endif //SPACEINVADERS_MENUOBRAZ_H