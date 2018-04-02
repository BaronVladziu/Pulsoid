#pragma once
#include "header.h"
#include "Floor.h"

Floor::Floor()
	: _counter(0)
{
	setSize(sf::Vector2f(800, 10));
	setOrigin(0, 0);
	setPosition(0, 440);
	setFillColor(sf::Color::White);
}
bool Floor::ifIsAlive()
{
	return (_counter > 0);
}
void Floor::add()
{
	_counter++;
}
void Floor::subtract()
{
	_counter--;
}
void Floor::draw(sf::RenderWindow & window)
{
	if (_counter > 0)
	{
		window.draw(*this);
	}
}
void Floor::restart()
{
	_counter = 0;
}