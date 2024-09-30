#ifndef NETWORK_HANDLER_HPP
#define NETWORK_HANDLER_HPP

#include <string>
#include <SFML/Network.hpp>

void sendMessage(sf::TcpSocket& socket, const std::string& name, std::string& msg);
bool reciveMessage(sf::TcpSocket& socket, std::string& nameRec, std::string& msgRec);
void startServer();
void startClient(const sf::IpAddress& ip);

#endif