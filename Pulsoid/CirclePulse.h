#pragma once
#include "header.h"

class CirclePulse
{
private:
	std::list<std::pair<sf::CircleShape, int>> _pulses;
	int _length;

public:
	CirclePulse();
	void addPulse(const sf::Vector2f & position, const float radius, const sf::Vector2f & origin);
	void update(const sf::Vector2f & position, const float radius, const sf::Vector2f & origin, const long double & state);
	void draw(sf::RenderWindow & window);
};