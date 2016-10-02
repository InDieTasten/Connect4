#include <iostream>

#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Connect4 by InDieTasten");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.display();
	}

	return EXIT_SUCCESS;
}