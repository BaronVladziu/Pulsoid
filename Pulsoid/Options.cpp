#pragma once
#include "header.h"
#include "Options.h"
#include "Button.h"
#include "GameState.h"

void Options::change()
{
	if (_ifChange == 0)
	{
		_vector[4]->setString(std::string("Apply"));
		_ifChange = 1;
	}
}

Options::Options(sf::Font & font)
	: _active(0), _fromWhere(0), _propVal(0), _ifChange(0)
{
	_Options.setCharacterSize(48);
	_Options.setFillColor(sf::Color::White);
	_Options.setStyle(sf::Text::Regular);
	_Options.setFont(font);
	_Options.setPosition(300, 20);
	_Options.setString("Options");

	_vector.push_back(new Button(font));
	int i = 170;
	_vector[0]->setPosition(sf::Vector2f(100.f, float(i)));
	_vector[0]->setString(std::string("Music Volume"));
	_vector[0]->_ifActive = 1;
	_SliderMUZ.setPosition(sf::Vector2f(450.f, float(i + 13)));

	_vector.push_back(new Button(font));
	i += 40;
	_vector[1]->setPosition(sf::Vector2f(100.f, float(i)));
	_vector[1]->setString(std::string("Screep Proporties"));

	_vector.push_back(new Button(font));
	i += 40;
	_vector[2]->setPosition(sf::Vector2f(100, float(i)));
	_vector[2]->setString(std::string("Antialiasing"));
	_SliderA.setPosition(sf::Vector2f(450.f, float(i + 13)));

	_vector.push_back(new Button(font));
	i += 40;
	_vector[3]->setPosition(sf::Vector2f(100.f, float(i)));
	_vector[3]->setString(std::string("Fullscreen"));
	_StampF.setPosition(sf::Vector2f(485.f, float(i)));

	_vector.push_back(new Button(font));
	i += 40;
	_vector[4]->setPosition(sf::Vector2f(100, float(i)));
	_vector[4]->setString(std::string("Back"));

	_proportions.push_back(new Button(font));
	i = 450;
	_proportions[0]->setSize(sf::Vector2f(80, 30));
	_proportions[0]->setPosition(sf::Vector2f(float(i), 210));
	_proportions[0]->setString(std::string("4:3"));
	_proportions[0]->_ifActive = 1;

	_proportions.push_back(new Button(font));
	i += 90;
	_proportions[1]->setSize(sf::Vector2f(80, 30));
	_proportions[1]->setPosition(sf::Vector2f(float(i), 210));
	_proportions[1]->setString(std::string("16:10"));

	_proportions.push_back(new Button(font));
	i += 90;
	_proportions[2]->setSize(sf::Vector2f(80, 30));
	_proportions[2]->setPosition(sf::Vector2f(float(i), 210));
	_proportions[2]->setString(std::string("16:9"));
}
Options::~Options()
{
	for (Button * el : _vector)
	{
		delete el;
	}
	for (Button * el : _proportions)
	{
		delete el;
	}
}
void Options::draw(sf::RenderWindow & window)
{
	window.draw(_Options);
	for (Button * el : _vector)
	{
		el->draw(window);
	}
	for (Button * el : _proportions)
	{
		el->draw(window);
	}
	_StampF.draw(window);
	_SliderA.draw(window);
	_SliderMUZ.draw(window);
}
void Options::up()
{
	if (_active > 0)
	{
		_vector[_active]->_ifActive = 0;
		_active--;
		_vector[_active]->_ifActive = 1;
	}
}
void Options::down()
{
	if (_active < 4)
	{
		_vector[_active]->_ifActive = 0;
		_active++;
		_vector[_active]->_ifActive = 1;
	}
}
void Options::active(sf::RenderWindow & window, sf::ContextSettings & settings, GameState & state, Effects & effects, Map & map)
{
	switch (_active)
	{
	case 3:
		if (state._ifFullscreen)
		{
			state._ifFullscreen = 0;
			_StampF._ifActive = 0;
			change();
		}
		else
		{
			state._ifFullscreen = 1;
			_StampF._ifActive = 1;
			change();
		}
		break;
	case 4:
		if (_ifChange == 1)
		{
			//zastosowanie ustawieñ
			window.create(sf::VideoMode(state._screenWidth, state._screenHeight), "Pulsoid", sf::Style::Default, settings);
			if (state._ifFullscreen)
			{
				sf::View view(window.getView());
				window.create(sf::VideoMode(state._screenWidth, state._screenHeight), "Pulsoid", sf::Style::Fullscreen, settings);
				window.setView(view);
			}
			_ifChange = 0;
			_vector[4]->setString(std::string("Back"));
		}
		else
		{
			//zapisywanie do pliku
			std::fstream plik_opcji("Options.ini");
			plik_opcji.clear();
			plik_opcji << "//Screen" << std::endl;
			plik_opcji << "16 : " << state._screenHeight * 16 / 800 << std::endl;
			plik_opcji << "fullscreen = " << state._ifFullscreen << std::endl;
			plik_opcji << "antialiasing = " << state._antialiasing << std::endl;
			plik_opcji << "//Volume" << std::endl;
			plik_opcji << "musicVolume = " << state._musicVolume << std::endl;
			plik_opcji.close();
			switch (_fromWhere)
			{
			case 0:
				state.setGameStateToMenu();
				break;
			case 1:
				state.setGameStateToPause();
				break;
			}
			break;
		}
	}
}
void Options::Slider_right(GameState & state)
{
	switch (_active)
	{
	case 0:
		++_SliderMUZ;
		if (state._musicVolume < 100)
		{
			state._musicVolume++;
			state.muzVol();
		}
		break;
	}
}
void Options::Slider_left(GameState & state)
{
	switch (_active)
	{
	case 0:
		--_SliderMUZ;
		if (state._musicVolume > 0)
		{
			state._musicVolume--;
			state.muzVol();
		}
		break;
	}
}
void Options::prop_right(GameState & state, sf::ContextSettings & settings)
{
	if (_active == 1)
	{
		if (_propVal < 2)
		{
			_proportions[_propVal]->_ifActive = 0;
			_propVal++;
			_proportions[_propVal]->_ifActive = 1;
			switch (_propVal)
			{
			case 1:
				state._screenHeight = 500;
				break;
			case 2:
				state._screenHeight = 450;
				break;
			}
			change();
		}
	}
	else if (_active == 2)
	{
		_SliderA + 25;
		switch (state._antialiasing)
		{
		case 0:
			state._antialiasing = 1;
			settings.antialiasingLevel = 1;
			break;
		case 1:
			state._antialiasing = 2;
			settings.antialiasingLevel = 2;
			break;
		case 2:
			state._antialiasing = 4;
			settings.antialiasingLevel = 4;
			break;
		case 4:
			state._antialiasing = 8;
			settings.antialiasingLevel = 8;
			break;
		}
		change();
	}
}
void Options::prop_left(GameState & state, sf::ContextSettings & settings)
{
	if (_active == 1)
	{
		if (_propVal > 0)
		{
			_proportions[_propVal]->_ifActive = 0;
			_propVal--;
			_proportions[_propVal]->_ifActive = 1;
			switch (_propVal)
			{
			case 0:
				state._screenHeight = 600;
				break;
			case 1:
				state._screenHeight = 500;
				break;
			}
			change();
		}
	}
	else if (_active == 2)
	{
		_SliderA - 25;
		switch (state._antialiasing)
		{
		case 1:
			state._antialiasing = 0;
			settings.antialiasingLevel = 0;
			break;
		case 2:
			state._antialiasing = 1;
			settings.antialiasingLevel = 1;
			break;
		case 4:
			state._antialiasing = 2;
			settings.antialiasingLevel = 2;
			break;
		case 8:
			state._antialiasing = 4;
			settings.antialiasingLevel = 4;
			break;
		}
		change();
	}
}
void Options::esc(GameState & state)
{
	switch (_fromWhere)
	{
	case 0:
		state.setGameStateToMenu();
		break;
	case 1:
		state.setGameStateToPause();
		break;
	}
}