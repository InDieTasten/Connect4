#include "Grid.hpp"

void Grid::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform.combine(this->getTransform());
	for (auto it : drawables)
		target.draw(it, states);
}

void Grid::update()
{
	drawables.clear();

	sf::RectangleShape rectShape;
	rectShape.setSize(sf::Vector2f(columnCount*cellWidth, rowCount*cellHeight));
	rectShape.setOutlineThickness(2.0f);
	rectShape.setOutlineColor(sf::Color::Blue);
	rectShape.setFillColor(sf::Color::Black);

	drawables.push_back(rectShape);

	for (unsigned int seperator = 1; seperator < columnCount; seperator++)
	{
		sf::RectangleShape rectShape;
		rectShape.setPosition(cellWidth * seperator, 0.0f);
		rectShape.setSize(sf::Vector2f(1.0f, rowCount*cellHeight));
		rectShape.setFillColor(sf::Color::White);
		rectShape.setOutlineColor(sf::Color::Green);
		rectShape.setOutlineThickness(1.0f);

		drawables.push_back(rectShape);
	}
}
