#include <iostream>

#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>

int main()
{

	std::cout << "[Info] Connect4 Client launched" << std::endl;

	while (true)
	{

		std::cout << "Insert host to play on: ";

		std::string insertedHoststring;

		std::cin >> insertedHoststring;

		std::cout << "[Info] Trying to connect to " << insertedHoststring << std::endl;

		sf::TcpSocket socket;

		sf::Socket::Status status = socket.connect(insertedHoststring, 1337);

		if (status != sf::Socket::Done)
		{
			std::cerr << "[Error] Unable to connect to " << insertedHoststring << std::endl;
		}
		else
		{
			std::cout << "[Info] Successfully connected to " << insertedHoststring << std::endl;
			
			int player;

			std::cout << "[Info] Retrieving player info..." << std::endl;
			sf::Packet packet;
			if (socket.receive(packet) != sf::Socket::Done)
			{
				std::cerr << "[Error] Couldn't retrieve player info" << std::endl;
			}
			else
			{
				int code;
				packet >> code;
				std::string message;

				switch (code)
				{
				case 201: //waiting packet, meaning this client is player 0
					packet >> message;
					std::cout << message << std::endl;
					player = 0;
					break;
				case 202: //player info packet, meaning this client in player 1
					packet >> message;
					std::cout << message << std::endl;
					player = 1;
					break;
				default:
					std::cerr << "[Error] Unexpected status code: " << code << std::endl;
					continue;
				}

				sf::Packet gamestartPacket;
				if (socket.receive(gamestartPacket) != sf::Socket::Done)
				{
					std::cerr << "[Error] Couldn't receive game start notification" << std::endl;
				}
				else
				{
					int code;
					gamestartPacket >> code;

					if (code == 300)
					{
						std::cout << "[Info] Game started!" << std::endl;
						std::cout << "You are player #" << player << std::endl;
						//
						sf::sleep(sf::seconds(10.0f));
					}
					else
					{
						std::cerr << "[Error] Unexpected status code: " << code << std::endl;
					}
				}
			}


		}
	}


	return EXIT_SUCCESS;
}
