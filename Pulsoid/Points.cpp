#pragma once
#include "header.h"
#include "Bonus.h"
#include "Points.h"

Points::Points()
	: _counter(0), _bonusType(9)
{
	_text.setCharacterSize(18);
	_text.setFillColor(sf::Color::White);
	_text.setPosition(10, 5);
	_text.setStyle(sf::Text::Regular);
	_text.setString("Points:");
	_number.setCharacterSize(18);
	_number.setFillColor(sf::Color::White);
	_number.setPosition(90, 5);
	_number.setStyle(sf::Text::Regular);
	_number.setString(std::to_string(_counter));
}
Points::~Points()
{
	for (Bonus * el : _floatingBonuses)
	{
		delete el;
	}
}
void Points::setFont(sf::Font & font)
{
	_font = font;
	_text.setFont(font);
	_number.setFont(font);
}
void Points::addPoints(sf::Vector2f & position, bool boosted)
{
	if (boosted)
	{
		_counter += 20;
		_number.setString(std::to_string(_counter));
	}
	else
	{
		_counter += 100;
		_number.setString(std::to_string(_counter));
		if (rand() % 5 == 0)
		{
			addBonus(position, rand() % 9);
		}
	}
}
void Points::subtractPoint()
{
	if (_counter != 0)
	{
		_counter -= 5;
		_number.setString(std::to_string(_counter));
	}
}
void Points::draw(sf::RenderWindow & window)
{
	window.draw(_text);
	window.draw(_number);
	for (Bonus * el : _floatingBonuses)
	{
		el->draw(window);
	}
}
void Points::restart()
{
	_counter = 0;
	_number.setString(std::to_string(_counter));
	for (Bonus * el : _floatingBonuses)
	{
		delete el;
	}
	_floatingBonuses.clear();
}
void Points::addBonus(sf::Vector2f & position, int type)
{
	_floatingBonuses.push_back(new Bonus(position, type, _font));
}
void Points::update(Player & player)
{
	for (std::list<Bonus *>::iterator it = _floatingBonuses.begin(); it != _floatingBonuses.end();)
	{
		(*it)->update(player);
		if ((*it)->_ifAlive == 0)
		{
			if ((*it)->_ifCatched == 1)
			{
				_bonusType = (*it)->_type;
			}
			std::list<Bonus *>::iterator it2 = it;
			it++;
			delete *it2;
			_floatingBonuses.erase(it2);
		}
		else
		{
			it++;
		}
	}
}
int Points::getPoints()
{
	return _counter;
}