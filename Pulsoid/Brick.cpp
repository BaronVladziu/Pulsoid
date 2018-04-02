#pragma once
#include "header.h"
#include "Brick.h"

Brick::Brick(int nr, int type) : _explosionTime(0), _timeToDie(300)
{
	setSize(sf::Vector2f(36, 11));
	setOrigin(-2, -2);
	setPosition((nr % 20) * 40, ((nr / 20) + 1) * 15);
	setOutlineThickness(4);
	_state = type;
	switch (type)
	{
	case 0:
		_explosion.zero();
		break;
	case 1:
		setFillColor(sf::Color::Transparent);
		setOutlineColor(sf::Color::White);
		break;
	case 2:
		setFillColor(sf::Color::White);
		setOutlineColor(sf::Color::White);
		break;
	case 3:
		setFillColor(sf::Color::Transparent);
		setOutlineColor(sf::Color::Transparent);
		break;
	}
	_explosion.setPosition(getPosition());
}
void Brick::explode()
{
	_explosionTime = 10;
	setOrigin(getOrigin() + sf::Vector2f(_explosionTime, _explosionTime));
	setSize(getSize() + sf::Vector2f(2 * _explosionTime, 2 * _explosionTime));
}
bool Brick::ifIsAlive()
{
	return (_state != 0);
}
bool Brick::ifDestroyed()
{
	return (_state != 0 && _state != 3);
}
bool Brick::ifWillDie()
{
	return (_state == 1);
}
void Brick::destroy()
{
	switch (_state)
	{
	case 1:
		_state = 0;
		break;
	case 2:
		_state = 1;
		setFillColor(sf::Color::Transparent);
		setOutlineColor(sf::Color::White);
		break;
	case 3:
		_state = 2;
		setFillColor(sf::Color::White);
		setOutlineColor(sf::Color::White);
	}
}
void Brick::update()
{
	if (_state == 0)
	{
		_explosion.update();
		if (_timeToDie > 0)
		{
			_timeToDie--;
		}
	}
	else
	{
		if (_explosionTime != 0)
		{
			_explosionTime--;
			setOrigin(getOrigin() - sf::Vector2f(1, 1));
			setSize(getSize() - sf::Vector2f(2, 2));
		}
	}
}
void Brick::draw(sf::RenderWindow & window)
{
	if (_state == 0)
	{
		_explosion.draw(window);
	}
	else
	{
		window.draw(*this);
	}
}