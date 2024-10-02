#include "NetworkHandler.hpp"
#include <thread>
#include <string>
#include <iostream>
#include <SFML/Network.hpp>


void startServer() {
    sf::TcpListener listener;
    sf::TcpSocket socket;

    if(listener.listen(2000) != sf::Socket::Done) {
        std::cout << "Error: listener err on port 2000\n";
        return;
    }

    if(listener.accept(socket) != sf::Socket::Done) {
        std::cout << "Error: could not accept socket\n";
        return;
    }
    
    std::string name = "Server";
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
