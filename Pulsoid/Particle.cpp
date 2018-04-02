#pragma once
#include "header.h"
#include "Particle.h"

Particle::Particle()
	: _acc(0.5), _state(1)
{
	setFillColor(sf::Color::White);
	setSize(sf::Vector2f(10, 10));
	setOrigin(0, 0);
	setPosition(sf::Vector2f(-100, -100));
	setRotation(float(rand()));
	_speed.x = float((rand() % 10) - 5);
	_speed.y = float((rand() % 10) - 8);
}
void Particle::setParticlePosition(sf::Vector2f position)
{
	setPosition(sf::Vector2f(position.x + 20, position.y + 7));
}
void Particle::update()
{
	move(_speed);
	rotate(_speed.x / 7);
	if (getPosition().y > 610)
	{
		_state = 0;
	}
	else
	{
		_speed.y += _acc;
	}
}
void Particle::drawParticle(sf::RenderWindow & window) const
{
	window.draw(*this);
}