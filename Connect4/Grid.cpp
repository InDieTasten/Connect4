#include "Grid.hpp"

bool Grid::persistCoin(unsigned int column, int player)
{
	if (level[column].size() < rowCount)
	{
		level[column].push_back(player);
		return true;
	}

	return false;
}

Grid::Grid(unsigned int _columnCount, unsigned int _rowCount)
{
	columnCount = _columnCount;
	rowCount = _rowCount;

	Reset();

	update();
}

bool Grid::InsertCoin(int player, sf::Vector2f position)
{
	sf::Vector2f transformedLocation = this->getInverseTransform().transformPoint(position);

	if (transformedLocation.y >= 0.0f && transformedLocation.y <= rowCount*cellHeight)
	{
		for (unsigned int column = 0; column < columnCount; column++)
		{
			float xpos = transformedLocation.x;
			if (xpos >= column * cellWidth && xpos < column * cellWidth + cellWidth)
			{
				//todo push coin
				return persistCoin(column, player);
			}
		}
	}

	return false;
}

void Grid::Reset()
{
	level.clear();

	for (unsigned int column = 0; column < columnCount; column++)
	{
		level.push_back(std::vector<int>());
	}
}

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
