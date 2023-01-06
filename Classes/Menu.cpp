//
// Created by adria on 6. 1. 2023.
//

#include "Menu.h"

Menu::Menu(float width, float height) {
    if (!font.loadFromFile("../Resources/space_invaders.ttf")) {
        std::cout << "Neexistuje.";
    }

    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Green);
    menu[0].setString("Nová Hra");
    menu[0].setCharacterSize(70);
    menu[0].setPosition(400, 200);

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::Green);
    menu[1].setString("Multiplayer");
    menu[1].setCharacterSize(70);
    menu[1].setPosition(400, 300);

    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::Green);
    menu[2].setString("Koniec");
    menu[2].setCharacterSize(70);
    menu[2].setPosition(400, 400);

    menuSelected = -1;
}

void Menu::draw(sf::RenderWindow& window) {
    for (int i = 0; i < 3; ++i) {
        window.draw(menu[i]);
    }
}

void Menu::Hore() {
    if (menuSelected - 1 >= 0) {
        menu[menuSelected].setFillColor(sf::Color::Green);

        menuSelected--;
        if (menuSelected == -1) {
            menuSelected = 2;
        }
        menu[menuSelected].setFillColor(sf::Color::Yellow);
    }
}

void Menu::Dole() {
    if (menuSelected + 1 <= 3) {
        menu[menuSelected].setFillColor(sf::Color::Green);

        menuSelected++;
        if (menuSelected == 4) {
            menuSelected = 0;
        }
        menu[menuSelected].setFillColor(sf::Color::Yellow);
    }
}

Menu::~Menu() {

}
