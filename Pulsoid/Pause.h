#pragma once
#include "header.h"

class Pause
{
private:
	sf::Text _pause;
	std::vector<Button *> _vector;
	/*
	0 - Back
	1 - Instruction
	2 - Options
	3 - Scores
	4 - Exit
	*/
	int _active;

public:
	Pause(sf::Font & font);
	~Pause();
	void draw(sf::RenderWindow & window);
	void up();
	void down();
	void active(sf::RenderWindow & window, GameState & state, Effects & effects, Map & map);
};