#include "GameRunner.hpp"

GameRunner::GameRunner(sf::TcpSocket & _player0, sf::TcpSocket & _player1)
	: player0(_player0), player1(_player1), grid(7,6)
{
}

void GameRunner::Run()
{
	while (true)
	{
		if (grid.CheckForWinner())
		{
			//send 402
			sf::Packet packet402;
			packet402 << 402;
			grid.AppendLevelToPacket(packet402);
			packet402 << grid.GetLastWinner();

			std::cout << "[Info] Player #" + std::to_string(grid.GetLastWinner()) + " has won the game" << std::endl;

			player0.send(packet402);
			player1.send(packet402);

			//end game
			break;
		}
		else if (!grid.IsSpaceLeft())
		{
			//send 403
			sf::Packet packet403;
			packet403 << 403;
			grid.AppendLevelToPacket(packet403);

			std::cout << "[Info] The game tied" << std::endl;

			player0.send(packet403);
			player1.send(packet403);

			//end game
			break;
		}
		else
		{
			//401 tell level
			sf::Packet packet401;
			packet401 << 401;
			grid.AppendLevelToPacket(packet401);

			std::cout << "[Info] Sending 401..." << std::endl;
			player0.send(packet401);
			player1.send(packet401);

			//send 410
			sf::Packet packet410;
			packet410 << 410 << grid.GetCurrentPlayer();
			std::cout << "[Info] Sending 410..." << std::endl;
			player0.send(packet410);
			player1.send(packet410);

			//wait for 500
			sf::Packet packet500;
			switch (grid.GetCurrentPlayer())
			{
			case 0:
				player0.receive(packet500);
				break;
			case 1:
				player1.receive(packet500);
				break;
			}
			int code;
			packet500 >> code;
			if (code == 500)
			{
				int column;
				packet500 >> column;
				std::cout << "[Info] Inserted coin to column: " << column << std::endl;
				grid.InsertCoin(column);
			}
		}
	}
}
