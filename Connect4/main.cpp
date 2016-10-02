#include <iostream>

#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>

int main()
{
	float fps = 30.0f;
	float supposedFrametime = 1.0f / fps;

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

		//framelimiter
		float usedtime = frameclock.getElapsedTime().asSeconds();
		float sparetime = supposedFrametime - usedtime;
		if (sparetime > 0.0f)
			sf::sleep(sf::seconds(sparetime));
		frameclock.restart();

		window.clear();
		window.display();
	}

	return EXIT_SUCCESS;
}