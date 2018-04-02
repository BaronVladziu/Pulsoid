#pragma once
#include "header.h"
#include "Brick.h"
#include "Bullet.h"
#include "GameState.h"

Bullet::Bullet(sf::Vector2f & position) : _speed(14), _ifAlive(1)
{
	setSize(sf::Vector2f(4, 10));
	setOrigin(2, 2);
	setPosition(position);
	setFillColor(sf::Color::White);
}
void Bullet::update(std::list<Brick *> & map, GameState & state)
{
	//kolizje z sufitem
	if (getPosition().y - _speed < 0)
	{
		_ifAlive = 0;
	}
	//kolizje z klockami
	for (Brick * el : map)
	{
		if (el->ifIsAlive())
		{
			if (getPosition().y - _speed > el->getPosition().y && getPosition().y - _speed < el->getPosition().y + 15)
			{
				if (getPosition().x > el->getPosition().x && getPosition().x < el->getPosition().x + 40)
				{
					el->destroy();
					_ifAlive = 0;
				}
			}
		}
	}
	//move
	setPosition(sf::Vector2f(getPosition().x, getPosition().y - _speed));
}