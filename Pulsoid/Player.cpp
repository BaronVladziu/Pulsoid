#pragma once
#include "header.h"
#include "Player.h"
#include "Bullet.h"
#include "Explosion.h"

Player::Player()
	: MAX_SPEED(10), _speed(0), _resistance(1.5), _acc(4), _size(2), _explosionTime(0), _deathTime(0)
{
	setSize(sf::Vector2f(116, 6));
	setOrigin(58, 3);
	setPosition(400, 430);
	setFillColor(sf::Color::Black);
	setOutlineThickness(4);
	setOutlineColor(sf::Color::White);
}
Player::~Player()
{
	for (Bullet * el : _bullets)
	{
		delete el;
	}
	for (Explosion * el : _particles)
	{
		delete el;
	}
}
void Player::animateDeath()
{
	_particles.push_back(new Explosion());
	_particles[0]->setPosition(getPosition() - sf::Vector2f(getSize().x / 2, 0));
	_particles.push_back(new Explosion());
	_particles[1]->setPosition(getPosition() - sf::Vector2f(getSize().x / 4, 0));
	_particles.push_back(new Explosion());
	_particles[2]->setPosition(getPosition());
	_particles.push_back(new Explosion());
	_particles[3]->setPosition(getPosition() + sf::Vector2f(getSize().x / 4, 0));
	_particles.push_back(new Explosion());
	_particles[4]->setPosition(getPosition() + sf::Vector2f(getSize().x / 2, 0));
	_deathTime = 60;
	setPosition(-10, -10);
}
void Player::addPulse()
{
	if (_deathTime == 0)
	{
		_pulse.addPulse(getPosition(), getSize(), getOrigin());
	}
}
void Player::explode()
{
	if (_deathTime == 0)
	{
		_explosionTime = 10;
		setOrigin(getOrigin() + sf::Vector2f(_explosionTime, _explosionTime));
		setSize(getSize() + sf::Vector2f(2 * _explosionTime, 2 * _explosionTime));
	}
}
void Player::shoot()
{
	_bullets.push_back(new Bullet(sf::Vector2f(getPosition().x - ((getSize().x + 4) / 2), getPosition().y)));
	_bullets.push_back(new Bullet(sf::Vector2f(getPosition().x + ((getSize().x + 4) / 2), getPosition().y)));
}
void Player::sizeUp()
{
	if (_size < 3)
	{
		setOrigin(getOrigin().x + 20, getOrigin().y);
		setSize(sf::Vector2f(getSize().x + 40, getSize().y));
		_size++;
	}
}
void Player::sizeDown()
{
	if (_size > 1)
	{
		setOrigin(getOrigin().x - 20, getOrigin().y);
		setSize(sf::Vector2f(getSize().x - 40, getSize().y));
		_size--;
	}
}
void Player::execute(std::list<Brick *> & map, GameState & state)
{
	//puls
	_pulse.update();
	if (_explosionTime != 0)
	{
		_explosionTime--;
		setOrigin(getOrigin() - sf::Vector2f(1, 1));
		setSize(getSize() - sf::Vector2f(2, 2));
	}
	//Trail gracza
	_playerTrail.update(getPosition(), _speed);
	//Bullet
	for (std::list<Bullet *>::iterator it = _bullets.begin(); it != _bullets.end();)
	{
		(*it)->update(map, state);
		if ((*it)->_ifAlive == 0)
		{
			std::list<Bullet *>::iterator it2 = it;
			it++;
			delete *it2;
			_bullets.erase(it2);
		}
		else
		{
			it++;
		}
	}
	//player
	if (_deathTime == 0)
	{
		//move
		move(_speed, 0);
		//sterowanie
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			_speed += _acc;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			_speed -= _acc;
		}
		//kolizje ze œcianami
		if (getPosition().x < getSize().x / 2)
		{
			setPosition((getSize().x / 2), getPosition().y);
			_speed *= -0.5;
		}
		else if (getPosition().x > 800 - (getSize().x / 2))
		{
			setPosition(800 - (getSize().x / 2), getPosition().y);
			_speed *= -0.5;
		}
		//obs³uga prêdkoœci
		else if (_speed >= -(_resistance) && _speed <= _resistance)
		{
			_speed = 0;
		}
		else if (_speed > 0)
		{
			_speed -= _resistance;
		}
		else
		{
			_speed += _resistance;
		}
		//ograniczenie prêdkoœci
		if (_speed > MAX_SPEED)
		{
			_speed = MAX_SPEED;
		}
		if (_speed < -MAX_SPEED)
		{
			_speed = -MAX_SPEED;
		}
	}
	else
	{
		_deathTime--;
		if (_deathTime == 0)
		{
			for (Explosion * el : _particles)
			{
				delete el;
			}
			_particles.clear();
			restart();
		}
		else
		{
			for (Explosion * el : _particles)
			{
				el->update();
			}
		}
	}
}
void Player::draw(sf::RenderWindow & window)
{
	_pulse.draw(window);
	_playerTrail.draw(window);
	for (Bullet * el : _bullets)
	{
		window.draw(*el);
	}
	if (_deathTime == 0)
	{
		window.draw(*this);
	}
	else
	{
		for (Explosion * el : _particles)
		{
			el->draw(window);
		}
	}
}
void Player::restart()
{
	_playerTrail.restart();
	_speed = 0;
	setPosition(400, 430);
}