#pragma once
#include "header.h"
#include "CirclePulse.h"

CirclePulse::CirclePulse() : _length(46) {}
void CirclePulse::addPulse(const sf::Vector2f & setPosition, const float radius, const sf::Vector2f & origin)
{
	std::pair<sf::CircleShape, int> puls;
	puls.second = 0;
	puls.first.setRadius(radius);
	puls.first.setOrigin(origin);
	puls.first.setPosition(setPosition);
	puls.first.setFillColor(sf::Color::Transparent);
	puls.first.setOutlineThickness(5);
	puls.first.setOutlineColor(sf::Color::White);
	_pulses.push_back(puls);
}
void CirclePulse::update(const sf::Vector2f & setPosition, const float radius, const sf::Vector2f & origin, const long double & state)
{
	for (std::list<std::pair<sf::CircleShape, int>>::iterator it = _pulses.begin(); it != _pulses.end();)
	{
		//sizeUpenie
		it->first.setOrigin(sf::Vector2f(300 * sin(state / (4.7 * 3.1415926535897932384626433832795)), 300 * sin(state / (4.7 * 3.1415926535897932384626433832795))));
		it->first.setRadius(300 * sin(state / (4.7 * 3.1415926535897932384626433832795)));
		it->second++;
		//usuwanie
		if (it->second > _length)
		{
			std::list<std::pair<sf::CircleShape, int>>::iterator it2 = it;
			it++;
			_pulses.erase(it2);
		}
		else
		{
			it++;
		}
	}
}
void CirclePulse::draw(sf::RenderWindow & window)
{
	for (std::pair<sf::CircleShape, int> & el : _pulses)
	{
		window.draw(el.first);
	}
}