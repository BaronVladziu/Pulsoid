#pragma once
#include "header.h"

class Map
{
public:
	std::list<Brick *> _map;
	std::fstream _plik;

	Map();
	~Map();
	void update(GameState & state, int points);
	void explode();
	void draw(sf::RenderWindow & window);
	void restart();
};