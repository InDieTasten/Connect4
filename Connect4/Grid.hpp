#pragma once

#include <SFML\Graphics.hpp>
#include <list>

class Grid : public sf::Drawable, public sf::Transformable
{
private:
	unsigned int columnCount;
	unsigned int rowCount;

	float cellWidth = 30.0f;
	float cellHeight = 30.0f;

	//components
	std::list<sf::RectangleShape> drawables;
public:
	Grid(unsigned int _columnCount, unsigned int _rowCount)
	{
		columnCount = _columnCount;
		rowCount = _rowCount;

		update();
	}

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	void update();
};
