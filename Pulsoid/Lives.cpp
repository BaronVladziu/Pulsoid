#pragma once
#include "header.h"
#include "GameState.h"
#include "Lives.h"

Lives::Lives()
	: _counter(3)
{
	_text.setCharacterSize(18);
	_text.setFillColor(sf::Color::White);
	_text.setPosition(700, 5);
	_text.setStyle(sf::Text::Regular);
	_text.setString("Lives:");
	_number.setCharacterSize(18);
	_number.setFillColor(sf::Color::White);
	_number.setPosition(770, 5);
	_number.setStyle(sf::Text::Regular);
	_number.setString(std::to_string(_counter));
}
void Lives::setFont(sf::Font & font)
{
	_text.setFont(font);
	_number.setFont(font);
}
void Lives::addLife()
{
	_counter++;
	_number.setString(std::to_string(_counter));
}
void Lives::subtractLife()
{
	_counter--;
	_number.setString(std::to_string(_counter));
}
void Lives::draw(sf::RenderWindow & window)
{
	window.draw(_text);
	window.draw(_number);
}
void Lives::ifPlayerDead(GameState & state)
{
	if (_counter <= 0)
	{
		state.setGameStateToMenu();
	}
}
void Lives::restart()
{
	_counter = 3;
	_number.setString(std::to_string(_counter));
}