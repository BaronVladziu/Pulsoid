#pragma once
#include "header.h"
#include "HorizontalTrail.h"

HorizontalTrail::HorizontalTrail()
	: _vanishing(0), _length(20)
{
	_shapes.resize(_length);
	for (int i = 0; i < _length; i++)
	{
		_shapes[i].setFillColor(sf::Color::White);
		_shapes[i].setSize(sf::Vector2f(0, 0));
		_shapes[i].setOrigin(0, 4);
		_shapes[i].setPosition(-10, -10);
	}
}
void HorizontalTrail::update(const sf::Vector2f & position, const float speed)
{
	//nowa setPosition dymku
	_shapes[_vanishing].setSize(sf::Vector2f(speed, 8));
	_shapes[_vanishing].setPosition(position);
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
void HorizontalTrail::draw(sf::RenderWindow & window)
{
	for (const sf::RectangleShape & el : _shapes)
	{
		window.draw(el);
	}
}
void HorizontalTrail::restart()
{
	for (sf::RectangleShape & el : _shapes)
	{
		el.setPosition(-10, -10);
	}
}