#include "GameClient.hpp"

GameClient::GameClient(sf::TcpSocket & _connection)
	: connection(_connection), grid(7,6)
{
}

void GameClient::Run(int player)
{
	float fps = 30.0f;
	float supposedFrametime = 1.0f / fps;

	grid.setScale(2.0f, 2.0f);

	grid.setPosition(50.0f, 50.0f);

	int gridWidth = 7;
	int gridHeight = 7;
	float cellWidth = 30.0f;
	float cellHeight = 30.0f;

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Connect4 by InDieTasten - Player #" + std::to_string(player));

	sf::Clock frameclock;

	connection.setBlocking(false);

	bool myTurn = false;

	while (window.isOpen())
	{
		//handle network events
		sf::Packet serverPacket;
		switch (connection.receive(serverPacket))
		{
		case sf::Socket::NotReady:
			break;
		case sf::Socket::Done:
			//Evaluate packet
			int code;
			serverPacket >> code;
			switch (code)
			{
			case 401: // load level
				std::cout << "[Info] Handling 401..." << std::endl;
				grid.LoadLevelFromPacket(serverPacket);
				break;
			case 402: // load level and winner
				grid.LoadLevelFromPacket(serverPacket);
				int winner;
				serverPacket >> winner;
				if (player == winner)
				{
					std::cout << "[Info] YOU WON THE GAME!!!" << std::endl;
				}
				else
				{
					std::cout << "[Info] YOU LOST THE GAME!!!" << std::endl;
				}
				window.close();
				break;
			case 403: // load level and tie
				grid.LoadLevelFromPacket(serverPacket);
				std::cout << "[Info] The game is tied" << std::endl;
				window.close();
				break;
			case 410: // turn notification
				std::cout << "[Info] Handling 410..." << std::endl;
				int turner;
				serverPacket >> turner;
				myTurn = turner == player;
				if (myTurn)
					std::cout << "[Info] It's your turn" << std::endl;
				break;
			}
			break;
		default:
			std::cerr << "[Error] Lost connection" << std::endl;
			window.close();
		}

		//handle window/user events
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				if (myTurn)
				{
					sf::Vector2f levelposition = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
					if (grid.InsertCoin(levelposition))
					{
						//send 500
						sf::Packet packet500;
						packet500 << 500 << grid.GetLastMove();

						std::cout << "[Info] Sending 500..." << std::endl;
						connection.send(packet500);
						myTurn = false;
					}
				}
				break;
			}
		}

		//clear frame
		window.clear();

		//draw shit
		grid.draw(window, sf::RenderStates());

		//framelimiter
		float usedtime = frameclock.getElapsedTime().asSeconds();
		float sparetime = supposedFrametime - usedtime;
		if (sparetime > 0.0f)
			sf::sleep(sf::seconds(sparetime));
		frameclock.restart();

		//display frame
		window.display();
	}

	connection.setBlocking(true);
}
