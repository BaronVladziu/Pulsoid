#pragma once
#include "header.h"
#include "RectanglePulse.h"

RectanglePulse::RectanglePulse()
	: _length(47)
{}
void RectanglePulse::addPulse(const sf::Vector2f & position, const sf::Vector2f & size, const sf::Vector2f & origin)
{
	std::pair<sf::RectangleShape, int> puls;
	puls.second = 0;
	puls.first.setSize(size);
	puls.first.setOrigin(origin);
	puls.first.setPosition(position);
	puls.first.setFillColor(sf::Color::Transparent);
	puls.first.setOutlineThickness(5);
	puls.first.setOutlineColor(sf::Color::White);
	_pulses.push_back(puls);
}
void RectanglePulse::update()
{
	for (std::list<std::pair<sf::RectangleShape, int>>::iterator it = _pulses.begin(); it != _pulses.end();)
	{
		//sizeUpenie
		it->first.setOrigin(it->first.getOrigin() + sf::Vector2f(15, 15));
		it->first.setSize(it->first.getSize() + sf::Vector2f(30, 30));
		it->second++;
		//usuwanie
		if (it->second > _length)
		{
			std::list<std::pair<sf::RectangleShape, int>>::iterator it2 = it;
			it++;
			_pulses.erase(it2);
		}
		else
		{
			it++;
		}
	}
}
void RectanglePulse::draw(sf::RenderWindow & window)
{
	for (std::pair<sf::RectangleShape, int> & el : _pulses)
	{
		window.draw(el.first);
	}
}