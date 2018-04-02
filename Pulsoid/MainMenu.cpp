#pragma once
#include "header.h"
#include "Effects.h"
#include "MainMenu.h"
#include "Button.h"
#include "GameState.h"

MainMenu::MainMenu(sf::Font & font) : _active(0)
{
	_pulsoid.setCharacterSize(72);
	_pulsoid.setFillColor(sf::Color::White);
	_pulsoid.setStyle(sf::Text::Regular);
	_pulsoid.setFont(font);
	_pulsoid.setPosition(230, 20);
	_pulsoid.setString("PULSOID");
	_vector.push_back(new Button(font));
	int i = 170;
	_vector[0]->setPosition(sf::Vector2f(60.f, float(i)));
	_vector[0]->setString(std::string("Play"));
	_vector[0]->_ifActive = 1;
	_vector.push_back(new Button(font));
	i += 50;
	_vector[1]->setPosition(sf::Vector2f(60.f, float(i)));
	_vector[1]->setString(std::string("Options"));
	_vector.push_back(new Button(font));
	i += 50;
	_vector[2]->setPosition(sf::Vector2f(60.f, float(i)));
	_vector[2]->setString(std::string("Scores"));
	_vector.push_back(new Button(font));
	i += 50;
	_vector[3]->setPosition(sf::Vector2f(60.f, float(i)));
	_vector[3]->setString(std::string("Authors"));
	_vector.push_back(new Button(font));
	i += 50;
	_vector[4]->setPosition(sf::Vector2f(60.f, float(i)));
	_vector[4]->setString(std::string("Exit"));
}
MainMenu::~MainMenu()
{
	for (Button * el : _vector)
	{
		delete el;
	}
}
void MainMenu::draw(sf::RenderWindow & window)
{
	window.draw(_pulsoid);
	for (Button * el : _vector)
	{
		el->draw(window);
	}
}
void MainMenu::up()
{
	if (_active > 0)
	{
		_vector[_active]->_ifActive = 0;
		_active--;
		_vector[_active]->_ifActive = 1;
	}
}
void MainMenu::down()
{
	if (_active < 4)
	{
		_vector[_active]->_ifActive = 0;
		_active++;
		_vector[_active]->_ifActive = 1;
	}
}
void MainMenu::update()
{
	//nie wiem, czy tu coœ bêdzie
}
void MainMenu::active(sf::RenderWindow & window, GameState & state, Effects & effects, Map & map)
{
	switch (_active)
	{
	case 0:
		state.setGameStateToGame();
		restart(effects, map);
		effects.restartTempo();
		break;
	case 1:
		state.setGameStateToOptions(0);
		break;
	case 2:
		state.setGameStateToScores(0, effects.getPoints());
		break;
	case 3:
		state.setGameStateToAuthors();
		break;
	case 4:
		window.close();
		break;
	}
}