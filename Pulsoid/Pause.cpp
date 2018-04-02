#pragma once
#include "header.h"
#include "Effects.h"
#include "Pause.h"
#include "Button.h"
#include "GameState.h"

Pause::Pause(sf::Font & font)
	: _active(0)
{
	_pause.setCharacterSize(48);
	_pause.setFillColor(sf::Color::White);
	_pause.setStyle(sf::Text::Regular);
	_pause.setFont(font);
	_pause.setPosition(300, 20);
	_pause.setString("Pause");
	_vector.push_back(new Button(font));
	int i = 170;
	_vector[0]->setPosition(sf::Vector2f(250.f, float(i)));
	_vector[0]->setString(std::string("Back"));
	_vector[0]->_ifActive = 1;
	_vector.push_back(new Button(font));
	i += 50;
	_vector[1]->setPosition(sf::Vector2f(250, float(i)));
	_vector[1]->setString(std::string("Options"));
	_vector.push_back(new Button(font));
	i += 50;
	_vector[2]->setPosition(sf::Vector2f(250, float(i)));
	_vector[2]->setString(std::string("Scores"));
	_vector.push_back(new Button(font));
	i += 50;
	_vector[3]->setPosition(sf::Vector2f(250, float(i)));
	_vector[3]->setString(std::string("Main Menu"));
}
Pause::~Pause()
{
	for (Button * el : _vector)
	{
		delete el;
	}
}
void Pause::draw(sf::RenderWindow & window)
{
	window.draw(_pause);
	for (Button * el : _vector)
	{
		el->draw(window);
	}
}
void Pause::up()
{
	if (_active > 0)
	{
		_vector[_active]->_ifActive = 0;
		_active--;
		_vector[_active]->_ifActive = 1;
	}
}
void Pause::down()
{
	if (_active < 3)
	{
		_vector[_active]->_ifActive = 0;
		_active++;
		_vector[_active]->_ifActive = 1;
	}
}
void Pause::active(sf::RenderWindow & window, GameState & state, Effects & effects, Map & map)
{
	switch (_active)
	{
	case 0:
		state.setGameStateToGame();
		break;
	case 1:
		state.setGameStateToOptions(1);
		break;
	case 2:
		state.setGameStateToScores(1, effects.getPoints());
		break;
	case 3:
		state.setGameStateToMenu();
		break;
	}
}