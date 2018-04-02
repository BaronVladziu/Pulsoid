#pragma once
#include "header.h"
#include "Bonus.h"

Bonus::Bonus(sf::Vector2f & position, int type, sf::Font & font) : _ifAlive(true), _ifCatched(false), _speed(2)
{
	_text.setCharacterSize(12);
	_text.setFillColor(sf::Color::White);
	_text.setStyle(sf::Text::Regular);
	_outline.setFillColor(sf::Color::White);
	_outline.setRadius(8);
	_outline.setOrigin(4, 4);
	_text.setPosition(sf::Vector2f(position.x + 35, position.y));
	_outline.setPosition(sf::Vector2f(position.x + 20, position.y + 7));
	_text.setFont(font);
	_type = type;
	switch (type)
	{
	case 0:
		_text.setString("Balls");
		break;
	case 1:
		_text.setString("Wide");
		break;
	case 2:
		_text.setString("Short");
		break;
	case 3:
		_text.setString("Pierce");
		break;
	case 4:
		_text.setString("Gun");
		break;
	case 5:
		_text.setString("Life");
		break;
	case 6:
		_text.setString("Floor");
		break;
	case 7:
		_text.setString("Fast");
		break;
	case 8:
		_text.setString("Slow");
		break;
	}
}
void Bonus::update(const Player & player)
{
	//kolizje z graczem
	if (_outline.getPosition().y + _speed + 7 > player.getPosition().y && _outline.getPosition().y + _speed - 7 < player.getPosition().y + 10)
	{
		float distance = _outline.getPosition().x - player.getPosition().x - 4;
		if (distance > -((player.getSize().x + 4) / 2) && distance < (player.getSize().x + 4) / 2)
		{
			_ifCatched = 1;
			_ifAlive = 0;
		}
	}
	//move
	_text.move(sf::Vector2f(0, _speed));
	_outline.move(sf::Vector2f(0, _speed));
	//umieranie
	if (_outline.getPosition().y > 620)
	{
		_ifAlive = 0;
	}
}
void Bonus::draw(sf::RenderWindow & window)
{
	window.draw(_outline);
	window.draw(_text);
}