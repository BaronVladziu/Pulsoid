#pragma once
#include "header.h"
#include "Brick.h"
#include "Map.h"
#include "GameState.h"

Map::Map()
{
	_plik.open("map.dat");
	int type;
	int i = 0;
	while (!_plik.eof())
	{
		_plik >> type;
		if (type >= 0 && type <= 3)
		{
			_map.push_back(new Brick(i, type));
			i++;
		}
	}
	_plik.close();
}
Map::~Map()
{
	for (Brick * el : _map)
	{
		delete el;
	}
}
void Map::update(GameState & state, int Points)
{
	for (std::list<Brick *>::iterator it = _map.begin(); it != _map.end();)
	{
		(*it)->update();
		if ((*it)->_timeToDie == 0)
		{
			std::list<Brick *>::iterator it2 = it;
			delete (*it);
			it++;
			_map.erase(it2);
		}
		else
		{
			it++;
		}
	}
	//czy win
	bool lost = 1;
	for (Brick * el : _map)
	{
		if (el->ifDestroyed())
		{
			lost = 0;
		}
	}
	if (lost == 1)
	{
		state.setGameStateToScores(2, Points);
	}
}
void Map::explode()
{
	for (Brick * el : _map)
	{
		el->explode();
	}
}
void Map::draw(sf::RenderWindow & window)
{
	for (Brick * el : _map)
	{
		el->draw(window);
	}
}
void Map::restart()
{
	for (Brick * el : _map)
	{
		delete el;
	}
	_map.clear();
	_plik.open("map.dat");
	int type;
	int i = 0;
	while (!_plik.eof())
	{
		_plik >> type;
		if (type >= 0 && type <= 3)
		{
			_map.push_back(new Brick(i, type));
			i++;
		}
	}
	_plik.close();
}