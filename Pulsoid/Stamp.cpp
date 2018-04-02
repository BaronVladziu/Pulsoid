#pragma once
#include "header.h"
#include "Stamp.h"

Stamp::Stamp()
	: _ifActive(0)
{
	_outline.setFillColor(sf::Color::Black);
	_outline.setOutlineColor(sf::Color::White);
	_outline.setOutlineThickness(4);
	_outline.setSize(sf::Vector2f(30, 30));
	_center.setFillColor(sf::Color::White);
	_center.setSize(sf::Vector2f(22, 22));
}
void Stamp::setSize(sf::Vector2f & size)
{
	_outline.setSize(size);
}
void Stamp::setPosition(sf::Vector2f & position)
{
	_outline.setPosition(position);
	_center.setPosition(sf::Vector2f(position.x + 4, position.y + 4));
}
void Stamp::draw(sf::RenderWindow & window)
{
	window.draw(_outline);
	if (_ifActive == 1)
	{
		window.draw(_center);
	}
}