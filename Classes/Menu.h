#include <iostream>
#include <SFML/Graphics.hpp>
//
// Created by adria on 6. 1. 2023.
//

#ifndef SPACEINVADERS_MENU_H
#define SPACEINVADERS_MENU_H


class Menu {
private:
    int menuSelected;
    sf::Text menu[2];
    sf::Font font;
public:
    Menu(float width, float height);
    void draw(sf::RenderWindow& window);
    void Hore();
    void Dole();

    int MenuPressed() const {
        return menuSelected;
    }

    ~Menu();


};


#endif //SPACEINVADERS_MENU_H
