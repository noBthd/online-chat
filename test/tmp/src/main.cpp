#include <iostream>
#include <thread>
#include <SFML/Network.hpp>
#include <string>


int main() {
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    sf::TcpSocket socket;

    char type;
    std::cout << "[s] - server\n[c] - client\n";
    std::cin >> type;

    if(type == 's') 
    {
        sf::TcpListener server;
        server.listen(2000);

        if(server.accept(socket) != sf::Socket::Done) 
        {
            std::cout << "Error!\n";
        }
    } 
    else if (type == 'c') 
    {
        if(socket.connect(ip, 2000) != sf::Socket::Done) 
        {
            std::cout << "Error!\n";
        }
    }

    std::string name;
    std::cout << "Enter your name: ";
    std::cin >> name;

    socket.setBlocking(false);

    std::string msg = "";
    sf::Packet packet;

    while (true)
    {
        std::cout << "msg: ";
        std::cin >> msg;

        if(msg != "")
        {
            packet.clear();
            packet << name << msg;

            socket.send(packet);
            msg = "";
        }

        if(socket.receive(packet) == sf::Socket::Done)
        {
            std::string nameRec;
            std::string msgRec;

            packet >> nameRec >> msgRec;
            std::cout << nameRec << ": " << msgRec << "\n";
        }
    }
    return 0;
}
