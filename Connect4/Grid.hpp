#pragma once

#include <SFML\Graphics.hpp>
#include <list>

class Grid : public sf::Drawable, public sf::Transformable
{
private:
	unsigned int columnCount;
	unsigned int rowCount;

	float cellWidth = 30.0f;
	float cellHeight = 26.0f;

	int player = 0;

	std::vector<std::vector<int>> level;

	bool persistCoin(unsigned int column, int player);

	//components
	std::list<sf::CircleShape> coins;
	std::list<sf::RectangleShape> drawables;
public:
	Grid(unsigned int _columnCount, unsigned int _rowCount);

	bool InsertCoin(sf::Vector2f position);
	void Reset();

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	void update();
};
