#pragma once
#include "header.h"
#include "Trail.h"

Trail::Trail()
	: _vanishing(0), _length(20)
{
	_vector.resize(_length);
	for (int i = 0; i < _length; i++)
	{
		_vector[i].setFillColor(sf::Color::White);
		_vector[i].setSize(sf::Vector2f(0, 0));
		_vector[i].setOrigin(0, 4);
		_vector[i].setPosition(-10, -10);
	}
}
void Trail::update(const sf::Vector2f & position, const float speed, const sf::Vector2f & velocity)
{
	//nowa pozycja dymku
	_vector[_vanishing].setSize(sf::Vector2f(speed + 2, 8));
	_vector[_vanishing].setPosition(position);
	//k¹t dymku
	if (velocity.y > 0)
	{
		_vector[_vanishing].setRotation(atan((-velocity.x) / velocity.y)*57.2958f - 90.f);
	}
	else
	{
		_vector[_vanishing].setRotation(atan((-velocity.x) / velocity.y)*57.2958f + 90.f);
	}
	//update _zanikaj¹cego
	if (_vanishing == _length - 1)
	{
		_vanishing = 0;
	}
	else
	{
		_vanishing++;
	}
}
void Trail::draw(sf::RenderWindow & window)
{
	for (const sf::RectangleShape & el : _vector)
	{
		window.draw(el);
	}
}
void Trail::restart()
{
	for (sf::RectangleShape & el : _vector)
	{
		el.setPosition(-10, -10);
	}
}