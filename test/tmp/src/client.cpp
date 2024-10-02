#include "NetworkHandler.hpp"
#include <thread>
#include <string>
#include <iostream>
#include <SFML/Network.hpp>


void startClient(sf::IpAddress ip) {
    sf::TcpSocket socket;

    if (socket.connect(ip, 2000) != sf::Socket::Done) {
        std::cout << "Error: can not connect to server";
        return;
    }

    std::string name;
    std::cout << "Name: ";
    std::cin >> name;

    socket.setBlocking(false);

    while (true)
    {
        std::string msg;
        std::cout << "msg: ";
        std::cin >> msg;

        if(msg != "") {
            sendMessage(socket, name, msg);
        }

        std::string nameRec, msgRec;
        if(reciveMessage(socket, nameRec, msgRec)) {
            std::cout << nameRec << ": " << msgRec;
        }
    }
    
}