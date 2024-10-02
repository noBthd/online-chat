#include <thread>
#include <string>
#include <iostream>
#include <SFML/Network.hpp>


void startServer(sf::TcpSocket& socket);
void startClient(sf::TcpSocket& socket);
void reciveMessage(sf::TcpSocket& socket, sf::Packet& packet);
void sendMessage(std::string& msg, std::string& name, sf::Packet& packet, sf::TcpSocket& socket);

int main() {
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    sf::TcpSocket socket;

    char type;
    std::cout << "[s] - server\n[c] - client\n";
    std::cin >> type;

    if(type == 's') 
    {
        startServer(socket);
    } 
    else if (type == 'c') 
    {
        startClient(socket);
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

        sendMessage(msg, name, packet, socket);
        // if(msg != "")
        // {
        //     packet.clear();
        //     packet << name << msg;

        //     socket.send(packet);
        //     msg = "";
        // }

        reciveMessage(socket, packet);
        // if(socket.receive(packet) == sf::Socket::Done)
        // {
        //     std::string nameRec;
        //     std::string msgRec;

        //     packet >> nameRec >> msgRec;
        //     std::cout << nameRec << ": " << msgRec << "\n";
        // }
    }
    return 0;
}

void startServer(sf::TcpSocket& socket) {
    sf::TcpListener server;
    server.listen(2000);

    if(server.accept(socket) != sf::Socket::Done) 
    {
        std::cout << "Error: server cannot accept socket\n";
    }
}

void startClient(sf::TcpSocket& socket) {
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();

    if(socket.connect(ip, 2000) != sf::Socket::Done) 
    {
        std::cout << "Error: client cannto connect to the socket\n";
    }
}

void reciveMessage(sf::TcpSocket& socket, sf::Packet& packet) {
    if(socket.receive(packet) == sf::Socket::Done)
    {
        std::string nameRec;
        std::string msgRec;

        packet >> nameRec >> msgRec;
        std::cout << nameRec << ": " << msgRec << "\n";
    }
}

void sendMessage(std::string& msg, std::string& name, sf::Packet& packet, sf::TcpSocket& socket) {
    if(msg != "")
    {
        packet.clear();
        packet << name << msg;
        socket.send(packet);

        msg = "";
    }
}