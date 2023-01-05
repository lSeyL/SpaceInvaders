//
// Created by seil0 on 5. 1. 2023.
//

#ifndef SPACEINVADERS_SERVER_H
#define SPACEINVADERS_SERVER_H

#include <SFML/Network.hpp>

class Server {

private:
    sf::TcpListener m_listener;
    sf::SocketSelector m_selector;
public:
    Server();
    ~Server();
    void spustiServer();

private:
    void spravujClienta(sf::TcpSocket* client);


};


#endif //SPACEINVADERS_SERVER_H
