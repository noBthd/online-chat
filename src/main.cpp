#include <list>
#include <thread>
#include <string>
#include <atomic>
#include <iostream>
#include <SFML/Network.hpp>


void startServer(sf::TcpSocket& socket);
void startClient(sf::TcpSocket& socket);
void reciveMessage(sf::TcpSocket& socket, sf::Packet& packet, std::atomic<bool>& isRunning);
void sendMessage(std::string& msg, std::string& name, sf::Packet& packet, sf::TcpSocket& socket);

class Client {
    private:

    protected:

    public:
        sf::IpAddress clientIp = sf::IpAddress::getLocalAddress();

        int clientId;
        std::string name;

        void print() {
            std::cout << clientIp << "\n";
            std::cout << clientId << "\n";
            std::cout << name     << "\n";
            
            std::cout.flush();
        }
};

class Chat {
    private:

    protected:

    public:
        sf::TcpSocket chatSocket;
        sf::Packet chatPacket;

        int chatId;
        std::string chatName;

        std::list<Client> clients = {};

        bool addClient(Client client) {
            clients.push_back(client);
            return true;
        }

        void info() {
            std::cout << chatId             << "\n";
            std::cout << chatName           << "\n";
            std::cout << clients.max_size() << "\n"

        }

};

class Server {
    Chat chats = {};
};

int main() {
    // sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    // sf::TcpSocket socket;
    // sf::Packet packet;

    // char type;
    // std::cout << "[s] - server\n[c] - client\n";
    // std::cin >> type;

    // if(type == 's') {
    //     startServer(socket);
    // } 
    // else if (type == 'c') {
    //     startClient(socket);
    // }

    // std::string name;
    // std::cout << "Enter your name: ";
    // std::cin >> name;

    // socket.setBlocking(false);

    // std::atomic<bool> isRunning(true);

    // std::thread t1(reciveMessage, std::ref(socket), std::ref(packet), std::ref(isRunning));

    // std::string msg = "";
    // while (isRunning) {
    //     std::cout << "msg: ";
    //     std::cin >> msg;

    //     if(msg == "/exit") 
    //         break;

    //     sendMessage(msg, name, packet, socket);
    // }

    // t1.join();

    Client client1 = {};
    Client client2{};

    Chat chat1{};

    chat1.addClient(client1);
    chat1.addClient(client2);

    int size = 2;

    Client mas[size];

    mas[0] = chat1.clients.back();
    chat1.clients.pop_back();
    mas[1] = chat1.clients.back();

    Client x = mas[0];
    Client y = mas[1];

    x.print();
    y.print();

    return 0;
}

void startServer(sf::TcpSocket& socket) {
    sf::TcpListener server;
    server.listen(2000);

    if(server.accept(socket) != sf::Socket::Done) {
        std::cout << "Error: server cannot accept socket\n";
    }
}
 
void startClient(sf::TcpSocket& socket) {
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();

    if(socket.connect(ip, 2000) != sf::Socket::Done) {
        std::cout << "Error: client cannto connect to the socket\n";
    }
}

void reciveMessage(sf::TcpSocket& socket, sf::Packet& packet, std::atomic<bool>& isRunning) {
    while(isRunning) {
        if(socket.receive(packet) == sf::Socket::Done) {
            std::string nameRec;
            std::string msgRec;
            packet >> nameRec >> msgRec;

            std::cout << nameRec << ": " << msgRec << "\n" << "msg: ";
            std::cout.flush();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void sendMessage(std::string& msg, std::string& name, sf::Packet& packet, sf::TcpSocket& socket) {
    if(msg != "") {
        packet.clear();
        packet << name << msg;
        if(socket.send(packet) != sf::Socket::Done) {
            std::cout << "Error sending message\n";
        }
        msg = "";
    }
}