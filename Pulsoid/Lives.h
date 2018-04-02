#pragma once
#include "header.h"

class Lives
{
private:
	sf::Text _number;
	sf::Text _text;
	int _counter;

public:
	Lives();
	void setFont(sf::Font & font);
	void addLife();
	void subtractLife();
	void draw(sf::RenderWindow & window);
	void ifPlayerDead(GameState & state);
	void restart();
};