#include <iostream>

#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include "Grid.hpp"

int main()
{
	float fps = 30.0f;
	float supposedFrametime = 1.0f / fps;

	Grid grid(7, 6);

	grid.setPosition(50.0f, 50.0f);

	int gridWidth = 7;
	int gridHeight = 7;
	float cellWidth = 30.0f;
	float cellHeight = 30.0f;

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Connect4 by InDieTasten");

	sf::Clock frameclock;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
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

	return EXIT_SUCCESS;
}

