#pragma once
#include "header.h"

class Explosion
{
private:
	std::vector<Particle *> _particles;
	int _number;

public:
	Explosion();
	~Explosion();
	void zero();
	void setPosition(sf::Vector2f position);
	void update();
	void draw(sf::RenderWindow & window);
};