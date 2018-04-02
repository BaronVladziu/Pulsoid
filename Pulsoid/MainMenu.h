#pragma once
#include "header.h"

class MainMenu
{
private:
	sf::Text _pulsoid;
	std::vector<Button *> _vector;
	/*
	0 - Play
	1 - Instruction
	2 - Options
	3 - Scores
	4 - Authors
	5 - Exit
	*/
	int _active;

public:
	MainMenu(sf::Font & font);
	~MainMenu();
	void draw(sf::RenderWindow & window);
	void up();
	void down();
	void update();
	void active(sf::RenderWindow & window, GameState & state, Effects & effects, Map & map);
};