#pragma once
#include "header.h"

class Stamp
{
private:
	sf::RectangleShape _center;
	sf::RectangleShape _outline;

public:
	bool _ifActive;

	Stamp();
	void setSize(sf::Vector2f & size);
	void setPosition(sf::Vector2f & position);
	void draw(sf::RenderWindow & window);
};