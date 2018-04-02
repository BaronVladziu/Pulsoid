#pragma once
#include "header.h"
#include "HorizontalTrail.h"
#include "RectanglePulse.h"

class Player
	: public sf::RectangleShape
{
private:
	float MAX_SPEED;
	float _resistance;
	float _acc;
	HorizontalTrail _playerTrail;
	int _size;
	std::list<Bullet *> _bullets;
	RectanglePulse _pulse;
	int _explosionTime;
	std::vector<Explosion *> _particles;

public:
	int _deathTime;
	float _speed;

	Player();
	~Player();
	void animateDeath();
	void addPulse();
	void explode();
	void shoot();
	void sizeUp();
	void sizeDown();
	void execute(std::list<Brick *> & map, GameState & state);
	void draw(sf::RenderWindow & window);
	void restart();
};