#include "Grid.hpp"

bool Grid::persistCoin(unsigned int column, int player)
{
	if (level[column].size() < rowCount)
	{
		level[column].push_back(player);
		update();
		return true;
	}

	return false;
}

bool Grid::checkForWinner(int _player)
{
	//check for verticals
	for (unsigned int column = 0; column < columnCount; column++)
	{
		unsigned int sequence = 0;
		for (unsigned int coin = 0; coin < level[column].size(); coin++)
		{
			if (level[column][coin] == _player)
				sequence++;
			else
				sequence = 0;

			if (sequence >= requiredToWin)
			{
				lastwinner = _player;
				return true;
			}
		}
	}

	//check for horizontals
	for (unsigned int row = 0; row < rowCount; row++)
	{
		unsigned int sequence = 0;
		for (unsigned int column = 0; column < columnCount; column++)
		{
			if (level[column].size() > row)
			{
				if (level[column][row] == _player)
				{
					sequence++;
				}
				else
				{
					sequence = 0;
				}
			}
			else
			{
				sequence = 0;
			}
			if (sequence >= requiredToWin)
			{
				lastwinner = _player;
				return true;
			}
		}
	}

	//check for diagonals (bottom left to top right)
	for (unsigned int column = 0; column < columnCount; column++)
	{
		for (unsigned int row = 0; row < rowCount; row++)
		{
			unsigned int sequence = 0;
			unsigned step = 0;

			while (column + step < columnCount && row + step < rowCount)
			{
				if (level[column+step].size() > row+step)
				{
					if (level[column+step][row+step] == _player)
					{
						sequence++;
					}
					else
					{
						sequence = 0;
					}
				}
				else
				{
					sequence = 0;
				}
				if (sequence >= requiredToWin)
				{
					lastwinner = _player;
					return true;
				}
				step++;
			}
		}
	}

	//check for diagonals (top left to bottom right)
	for (unsigned int column = 0; column < columnCount; column++)
	{
		for (int row = rowCount-1; row >= 0; row--)
		{
			unsigned int sequence = 0;
			unsigned step = 0;

			while (column + step < columnCount && row - step >= 0)
			{
				if (level[column + step].size() > row - step)
				{
					if (level[column + step][row - step] == _player)
					{
						sequence++;
					}
					else
					{
						sequence = 0;
					}
				}
				else
				{
					sequence = 0;
				}
				if (sequence >= requiredToWin)
				{
					lastwinner = _player;
					return true;
				}
				step++;
			}
		}
	}

	return false;
}

Grid::Grid(unsigned int _columnCount, unsigned int _rowCount)
{
	columnCount = _columnCount;
	rowCount = _rowCount;

	Reset();
}

bool Grid::InsertCoin(sf::Vector2f position)
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
				if (persistCoin(column, player))
				{
					player = (player + 1) % 2;
					update();
					return true;
				}
			}
		}
	}

	return false;
}

bool Grid::CheckForWinner()
{
	return checkForWinner(0) || checkForWinner(1);
}

void Grid::Reset()
{
	level.clear();

	for (unsigned int column = 0; column < columnCount; column++)
	{
		level.push_back(std::vector<int>());
	}

	update();
}

int Grid::GetLastWinner()
{
	return lastwinner;
}

void Grid::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform.combine(this->getTransform());
	for (auto it : drawables)
		target.draw(it, states);

	for (auto it : coins)
		target.draw(it, states);
}

void Grid::update()
{
	drawables.clear();

	sf::RectangleShape rectShape;
	rectShape.setSize(sf::Vector2f(columnCount*cellWidth, rowCount*cellHeight));
	rectShape.setOutlineThickness(2.0f);
	switch (player)
	{
	case 0:
		rectShape.setOutlineColor(sf::Color::Blue);
		break;
	case 1:
		rectShape.setOutlineColor(sf::Color::Red);
	}
	rectShape.setFillColor(sf::Color::Black);

	drawables.push_back(rectShape);

	for (unsigned int seperator = 1; seperator < columnCount; seperator++)
	{
		sf::RectangleShape rectShape;
		rectShape.setPosition(cellWidth * seperator, 0.0f);
		rectShape.setSize(sf::Vector2f(1.0f, rowCount*cellHeight));
		rectShape.setFillColor(sf::Color::White);
		rectShape.setOutlineColor(sf::Color::Green);
		rectShape.setOutlineThickness(0.0f);

		drawables.push_back(rectShape);
	}

	coins.clear();

	for (unsigned int column = 0; column < columnCount; column++)
	{
		for (unsigned int coin = 1; coin < level[column].size()+1; coin++)
		{
			sf::CircleShape circle;
			circle.setRadius(cellHeight / 2.0f);
			switch (level[column][coin - 1])
			{
			case 0:
				circle.setFillColor(sf::Color::Blue);
				break;
			case 1:
				circle.setFillColor(sf::Color::Red);
			}
			circle.setPosition(column*cellWidth+2.0f, rowCount*cellHeight - coin*cellHeight);

			coins.push_back(circle);
		}
	}
}
