#include "NetworkHandler.hpp"
#include <iostream>


void sendMessage(sf::TcpSocket& socket, const std::string& name, std::string& msg) {
    sf::Packet packet;

    packet.clear();
    packet << name << msg;
    socket.send(packet);
    msg = "";
}

bool reciveMessage(sf::TcpSocket& socket, std::string& nameRec, std::string& msgRec) {
    sf::Packet packet;

    if(socket.receive(packet) == sf::Socket::Done) {
        packet >> nameRec >> msgRec;
        return true;
    }

    return false;
}