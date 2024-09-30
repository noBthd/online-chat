#include <iostream>
#include <thread>
#include <SFML/Network.hpp>
#include <string>
#include "NetworkHandler.hpp"


int main() {
    char type;
    std::cout << "[s] - server\n[c] - client\n";
    std::cin >> type;

    if(type == 's') 
    {
        startServer();
    } 
    else if (type == 'c') 
    {
        sf::IpAddress ip = sf::IpAddress::getLocalAddress();
        startClient(ip);
    }

    return 0;
}
