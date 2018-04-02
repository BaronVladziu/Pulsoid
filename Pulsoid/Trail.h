#pragma once
#include "header.h"

class Trail
{
private:
	int _vanishing;
	int _length;
	std::vector<sf::RectangleShape> _vector;

public:
	Trail();
	void update(const sf::Vector2f & position, const float speed, const sf::Vector2f & velocity);
	void draw(sf::RenderWindow & window);
	void restart();
};