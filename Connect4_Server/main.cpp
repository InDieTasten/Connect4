#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include "gamerunner.hpp"

int main()
{

	std::cout << "[Info] Connect4 Server launched" << std::endl;

	while (true)
	{
		std::cout << "[Info] Waiting for players..." << std::endl;

		sf::TcpListener listener;

		if (listener.listen(1337) != sf::Socket::Done)
		{
			std::cerr << "[Error] Oh noes!! An error occured" << std::endl;
		}
		else
		{
			sf::TcpSocket player0;

			if (listener.accept(player0) != sf::Socket::Done)
			{
				std::cerr << "[Error] Oh noes!! An error occured" << std::endl;
			}
			else
			{
				std::cout << "[Info] Player #0 connected. Waiting for opponent..." << std::endl;
				sf::Packet player0WaitingPacket;
				player0WaitingPacket << 201 << "[Info] Waiting for opponent...";
				if (player0.send(player0WaitingPacket) != sf::Socket::Done)
				{
					std::cerr << "[Error] Player #0 couldn't receive waiting packet" << std::endl;
				}
				else
				{
					sf::TcpSocket player1;

					if (listener.accept(player1) != sf::Socket::Done)
					{
						std::cerr << "[Error] Oh noes!! An error occured" << std::endl;
					}
					else
					{
						std::cout << "[Info] Player #1 connected!" << std::endl;
						sf::Packet player1playerInfo;
						player1playerInfo << 202 << "[Info] Player #0 already awaited you";
						if (player1.send(player1playerInfo) != sf::Socket::Done)
						{
							std::cerr << "[Error] Player #1 couldn't receive player info packet" << std::endl;
						}
						else
						{
							sf::Packet gamestartedPacket;
							gamestartedPacket << 300;

							if (player0.send(gamestartedPacket) != sf::Socket::Done)
							{
								std::cerr << "[Error] Player #0 couldn't receive game start notification" << std::endl;
							}
							else
							{
								if (player1.send(gamestartedPacket) != sf::Socket::Done)
								{
									std::cerr << "[Error] Player #1 couldn't receive game start notification" << std::endl;
								}
								else
								{
									GameRunner gameRunner(player0, player1);
									gameRunner.Run();
								}

							}
						}
					}
				}
			}
		}
	}

	return EXIT_SUCCESS;
}
