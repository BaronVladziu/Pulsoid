#pragma once
#include "header.h"
#include "Player.h"
#include "Lives.h"
#include "Points.h"
#include "Ammo.h"
#include "Floor.h"

class Effects
{
private:
	std::list<Ball *> _balls;
	Player _player;
	Lives _lives;
	Points _points;
	Ammo _ammo;
	Floor _floor;
	std::vector<int> _effects;
	long double _pulseState;
	int _shooting;

	void looseLife();
	void addEffect(int type, GameState & state);
	void updateEffects(GameState & state);

public:
	Effects(sf::Font & font);
	~Effects();
	void update(Map & map, GameState & state);
	void puls(Map & map);
	void restartTempo();
	void shoot(GameState & state);
	void draw(sf::RenderWindow & window);
	void restart();
	int getPoints();
};