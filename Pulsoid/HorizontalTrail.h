#pragma once
#include "header.h"

class HorizontalTrail
{
private:
	int _vanishing;
	int _length;
	std::vector<sf::RectangleShape> _shapes;

public:
	HorizontalTrail();
	void update(const sf::Vector2f & position, const float speed);
	void draw(sf::RenderWindow & window);
	void restart();
};