//
// Created by seil0 on 5. 1. 2023.
//

#include "Server.h"

Server::Server()  : m_listener(), m_selector() {
    if (m_listener.listen(53000) != sf::Socket::Done)
    {
        //error
    }

    //
    m_selector.add(m_listener);
}

Server::~Server() {

}

void Server::spustiServer() {
    while (true)
    {
        if (m_selector.wait()){
            if(m_selector.isReady(m_listener))
            {
                sf::TC
            }
        }
    }
}

void Server::spravujClienta(sf::TcpSocket *client) {

}
