#pragma once
#include "header.h"
#include "Particle.h"
#include "Explosion.h"

Explosion::Explosion()
	: _number(10)
{
	for (int i = 0; i < _number; i++)
	{
		_particles.push_back(new Particle());
	}
}
Explosion::~Explosion()
{
	for (Particle * el : _particles)
	{
		delete el;
	}
}
void Explosion::zero()
{
	for (Particle * el : _particles)
	{
		delete el;
	}
	_particles.clear();
}
void Explosion::setPosition(sf::Vector2f position)
{
	for (Particle * el : _particles)
	{
		el->setParticlePosition(position);
	}
}
void Explosion::update()
{
	for (Particle * el : _particles)
	{
		if (el->_state == 1)
		{
			el->update();
		}
	}
}
void Explosion::draw(sf::RenderWindow & window)
{
	for (Particle * el : _particles)
	{
		if (el->_state == 1)
		{
			el->drawParticle(window);
		}
	}
}