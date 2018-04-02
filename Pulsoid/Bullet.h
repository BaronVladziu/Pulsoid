#pragma once
#include "header.h"

class Bullet
	: public sf::RectangleShape
{
private:
	float _speed;

public:
	bool _ifAlive;

	Bullet(sf::Vector2f & position);
	void update(std::list<Brick *> & map, GameState & state);
};