#pragma once

#include <iostream>
#include <SFML\Network.hpp>
#include "Grid.hpp"

class GameRunner
{
private:
	sf::TcpSocket& player0;
	sf::TcpSocket& player1;

	Grid grid;

	void handle401();

public:
	GameRunner(sf::TcpSocket& _player0, sf::TcpSocket& _player1);

	void Run();
};