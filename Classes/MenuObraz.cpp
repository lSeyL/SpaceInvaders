//
// Created by adria on 6. 1. 2023.
//

#include "MenuObraz.h"

MenuObraz::MenuObraz() {


}


MenuObraz::~MenuObraz() {

}

void MenuObraz::zobrazMenu() {
    sf::RenderWindow menu(sf::VideoMode(SIRKA_OBRAZOVKY, VYSKA_OBRAZOVKY), "Space Invaders");
    Menu gameMenu(menu.getSize().x, menu.getSize().y);

    sf::RectangleShape pozadie(sf::Vector2f(SIRKA_OBRAZOVKY, VYSKA_OBRAZOVKY));
    sf::Texture menuTex;
    menuTex.loadFromFile("../Resources/menu.png");
    pozadie.setTexture(&menuTex);

    while (menu.isOpen()) {
        sf::Event event;
        while (menu.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                menu.close();
            }

            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Up) {
                    gameMenu.Hore();
                    break;
                }
                if (event.key.code == sf::Keyboard::Down) {
                    gameMenu.Dole();
                    break;
                }
                if (event.key.code == sf::Keyboard::Return) {
                    sf::RenderWindow novaHra(sf::VideoMode(SIRKA_OBRAZOVKY, VYSKA_OBRAZOVKY), "Nová Hra");
                    sf::RenderWindow multiplayer(sf::VideoMode(SIRKA_OBRAZOVKY, VYSKA_OBRAZOVKY), "Nová Hra");

                    int x = gameMenu.MenuPressed();
                    if (x == 0) {
                        while (novaHra.isOpen()) {
                            sf::Event aEvent;
                            while (novaHra.pollEvent(aEvent)) {
                                if (aEvent.type == sf::Event::Closed) {
                                    novaHra.close();
                                }
                                if (aEvent.type == sf::Event::KeyPressed) {
                                    if (aEvent.key.code == sf::Keyboard::Escape) {
                                        novaHra.close();
                                    }
                                }
                            }
                            multiplayer.close();
                            novaHra.clear();
                            novaHra.display();
                        }
                    }
                    if (x == 1) {
                        while (multiplayer.isOpen()) {
                            sf::Event aEvent;
                            while (multiplayer.pollEvent(aEvent)) {
                                if (aEvent.type == sf::Event::Closed) {
                                    multiplayer.close();
                                }
                                if (aEvent.type == sf::Event::KeyPressed) {
                                    if (aEvent.key.code == sf::Keyboard::Escape) {
                                        multiplayer.close();
                                    }
                                }
                            }
                            novaHra.close();
                            multiplayer.clear();
                            multiplayer.display();
                        }
                    }
                    if (x == 2) {
                        menu.close();
                    }
                }
            }

        }
    }
    menu.clear();
    menu.draw(pozadie);
    gameMenu.draw(menu);
    menu.display();
}