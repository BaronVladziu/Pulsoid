#pragma once
#include "header.h"
#include "Button.h"

Button::Button(sf::Font & font)
	: _ifActive(0)
{
	_text.setCharacterSize(24);
	_text.setFillColor(sf::Color::White);
	_text.setStyle(sf::Text::Regular);
	_text.setFont(font);
	_outline.setFillColor(sf::Color::Black);
	_outline.setOutlineColor(sf::Color::White);
	_outline.setOutlineThickness(4);
	_outline.setSize(sf::Vector2f(300, 30));
}
void Button::setString(std::string & text)
{
	_text.setString(text);
}
void Button::setSize(sf::Vector2f & size)
{
	_outline.setSize(size);
}
void Button::setPosition(sf::Vector2f & setPosition)
{
	_text.setPosition(sf::Vector2f(setPosition.x + 10, setPosition.y));
	_outline.setPosition(setPosition);
}
void Button::draw(sf::RenderWindow & window)
{
	if (_ifActive == 1)
	{
		window.draw(_outline);
	}
	window.draw(_text);
}