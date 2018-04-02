#pragma once
#include "header.h"
#include "Explosion.h"

class Brick
	: public sf::RectangleShape
{
private:
	int _explosionTime;
	int _state;

public:
	Explosion _explosion;
	/*
	0 - zniszczony
	1 - ca³y
	2 - wzmocniony
	3 - niewidzialny
	*/
	int _timeToDie;

	Brick(int nr, int type);
	void explode();
	bool ifIsAlive();
	bool ifDestroyed();
	bool ifWillDie();
	void destroy();
	void update();
	void draw(sf::RenderWindow & window);
};