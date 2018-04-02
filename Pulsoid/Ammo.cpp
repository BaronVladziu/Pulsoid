#pragma once
#include "header.h"
#include "Ammo.h"

Ammo::Ammo()
	: _counter(0)
{
	_text.setCharacterSize(18);
	_text.setFillColor(sf::Color::White);
	_text.setPosition(340, 5);
	_text.setStyle(sf::Text::Regular);
	_text.setString("Ammo:");
	_number.setCharacterSize(18);
	_number.setFillColor(sf::Color::White);
	_number.setPosition(445, 5);
	_number.setStyle(sf::Text::Regular);
	_number.setString(std::to_string(_counter));
}
void Ammo::setFont(sf::Font & font)
{
	_text.setFont(font);
	_number.setFont(font);
}
void Ammo::addAmmo()
{
	_counter += 20;
	_number.setString(std::to_string(_counter));
}
void Ammo::subtractAmmo()
{
	_counter--;
	_number.setString(std::to_string(_counter));
}
void Ammo::draw(sf::RenderWindow & window)
{
	window.draw(_text);
	window.draw(_number);
}
bool Ammo::ifAnyAmmo()
{
	return (_counter > 0);
}
void Ammo::restart()
{
	_counter = 0;
	_number.setString(std::to_string(_counter));
}