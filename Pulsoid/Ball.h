#pragma once
#include "header.h"
#include "Trail.h"
#include "CirclePulse.h"

class Ball
	: public sf::CircleShape
{
private:
	int _pause;
	Trail _ballTrail;
	bool _ifBoosted;
	CirclePulse _pulse;
	int _explosionTime;

	void keepEnergy();
	void destroy(Brick & el, std::list<Brick *> & map, Points & points, GameState & state);
	void destroyBrick(std::list<Brick *> & map, Points & points, GameState & state);

public:
	bool _ifAlive;
	float _speed;
	int _state;
	sf::Vector2f _velocity;

	Ball();
	Ball(const sf::Vector2f & setPosition, float speed, int state);
	void Explosion(int _deathTime);
	void addPulse(int _deathTime);
	void speedUp();
	void speedDown();
	void boost();
	void unboost();
	void execute(Map & map, const Player & player, Points & points, Floor & floor, const long double & pulseState, GameState & state);
	void draw(sf::RenderWindow & window, int _deathTime);
};