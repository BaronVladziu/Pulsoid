#pragma once
#include "header.h"

class Particle
	: private sf::RectangleShape
{
private:
	sf::Vector2f _speed;
	float _acc;

public:
	bool _state;

	Particle();
	void setParticlePosition(sf::Vector2f position);
	void update();
	void drawParticle(sf::RenderWindow & window) const;
};