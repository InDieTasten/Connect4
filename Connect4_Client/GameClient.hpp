#pragma once

#include <iostream>
#include <SFML\Network.hpp>
#include "Grid.hpp"

class GameClient
{
private:
	Grid grid;
	sf::TcpSocket& connection;
public:
	GameClient(sf::TcpSocket& _connection);

	void Run(int player);
};