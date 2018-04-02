#pragma once
#include "header.h"
#include "Options.h"
#include "Scores.h"
#include "Authors.h"

class GameState
{
private:
	sf::Music _music1;
	sf::Music _music2;

public:
	int _gameState;
	int _screenWidth;
	int _screenHeight;
	int _antialiasing;
	int _musicVolume;
	bool _ifFullscreen;
	Scores _Scores;
	Options _Options;
	Authors _authors;
	/*
	0 - Main Menu
	1 - Game
	2 - Instruction from Menu
	3 - Options from Menu
	4 - Scores from Menu
	5 - Authors
	6 - Pause
	*/

	GameState(sf::Font & font);
	void configure(const std::string & text, int number);
	void muzVol();
	void setGameStateToMenu();
	bool ifGameStateMenu();
	void setGameStateToGame();
	bool ifGameStateGame();
	void setGameStateToOptions(bool fromWhere);
	bool ifGameStateOptions();
	void setGameStateToScores(int fromWhere, int points);
	bool ifGameStateScores();
	void setGameStateToAuthors();
	bool ifGameStateAuthors();
	void setGameStateToPause();
	bool ifGameStatePause();
};