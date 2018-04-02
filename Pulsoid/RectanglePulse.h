#pragma once
#include "header.h"

class RectanglePulse
{
private:
	std::list<std::pair<sf::RectangleShape, int>> _pulses;
	int _length;

public:
	RectanglePulse();
	void addPulse(const sf::Vector2f & position, const sf::Vector2f & size, const sf::Vector2f & origin);
	void update();
	void draw(sf::RenderWindow & window);
};