#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <list>

class Grid : public sf::Drawable, public sf::Transformable
{
private:
	unsigned int columnCount;
	unsigned int rowCount;

	float cellWidth = 30.0f;
	float cellHeight = 26.0f;

	unsigned int requiredToWin = 4;

	int player = 0;
	int lastwinner = 1;
	int turns = 0;
	std::vector<std::vector<int>> level;

	bool checkForWinner(int player);

	//components
	std::list<sf::CircleShape> coins;
	std::list<sf::RectangleShape> drawables;
public:
	Grid(unsigned int _columnCount, unsigned int _rowCount);

	bool InsertCoin(unsigned int column);
	bool CheckForWinner();
	void Reset();
	int GetLastWinner();
	bool IsSpaceLeft();
	int GetCurrentPlayer();

	//Networking
	void AppendLevelToPacket(sf::Packet& packet);

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	void update();
};
