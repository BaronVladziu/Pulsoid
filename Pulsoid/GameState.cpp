#pragma once
#include "header.h"
#include "GameState.h"

GameState::GameState(sf::Font & font)
	: _gameState(0), _Scores(font), _ifFullscreen(false), _Options(font), _authors(font), _antialiasing(0)
{
	_music1.openFromFile("GameMusic1.ogg");
	_music1.setLoop(1);
	_music1.setVolume(30);
	_music2.openFromFile("GameMusic2.ogg");
	_music2.setLoop(1);
	_music2.setVolume(30);
	_music2.play();
}
void GameState::configure(const std::string & text, int number)
{
	if (text == "16")
	{
		_screenWidth = 800;
		_screenHeight = 800 / 16 * number;
		switch (number)
		{
		case 12:
			_Options._propVal = 0;
			break;
		case 10:
			_Options._propVal = 1;
			_Options._proportions[0]->_ifActive = 0;
			_Options._proportions[1]->_ifActive = 1;
			break;
		case 9:
			_Options._propVal = 2;
			_Options._proportions[0]->_ifActive = 0;
			_Options._proportions[2]->_ifActive = 1;
			break;
		}
	}
	else if (text == "musicVolume")
	{
		_musicVolume = number;
		muzVol();
		_Options._SliderMUZ.setValue(number);
	}
	else if (text == "fullscreen")
	{
		_ifFullscreen = bool(number);
		_Options._StampF._ifActive = bool(number);
	}
	else if (text == "antialiasing")
	{
		_antialiasing = number;
		switch (number)
		{
		case 0:
			_Options._SliderA.setValue(0);
			break;
		case 1:
			_Options._SliderA.setValue(25);
			break;
		case 2:
			_Options._SliderA.setValue(50);
			break;
		case 4:
			_Options._SliderA.setValue(75);
			break;
		case 8:
			_Options._SliderA.setValue(100);
			break;
		}
	}
}
void GameState::muzVol()
{
	_music1.setVolume(float(_musicVolume));
	_music2.setVolume(float(_musicVolume));
}
void GameState::setGameStateToMenu()
{
	_gameState = 0;
	if (_music2.getStatus() == sf::Music::Playing)
	{
	}
	else
	{
		_music1.stop();
		_music2.play();
	}
}
bool GameState::ifGameStateMenu()
{
	return (_gameState == 0);
}
void GameState::setGameStateToGame()
{
	_gameState = 1;
	if (_music2.getStatus() == sf::Music::Playing)
	{
		_music2.stop();
	}
	_music1.play();
}
bool GameState::ifGameStateGame()
{
	return (_gameState == 1);
}
void GameState::setGameStateToOptions(bool fromWhere)
{
	_gameState = 3;
	_Options._fromWhere = fromWhere;
}
bool GameState::ifGameStateOptions()
{
	return (_gameState == 3);
}
void GameState::setGameStateToScores(int fromWhere, int points)
{
	_gameState = 4;
	_Scores._fromWhere = fromWhere;
	if (fromWhere == 2)
	{
		_Scores.win(points);
	}
}
bool GameState::ifGameStateScores()
{
	return (_gameState == 4);
}
void GameState::setGameStateToAuthors()
{
	_gameState = 5;
}
bool GameState::ifGameStateAuthors()
{
	return (_gameState == 5);
}
void GameState::setGameStateToPause()
{
	_gameState = 6;
	_music1.pause();
}
bool GameState::ifGameStatePause()
{
	return (_gameState == 6);
}