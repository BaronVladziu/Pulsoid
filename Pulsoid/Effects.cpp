#pragma once
#include "header.h"
#include "Effects.h"
#include "Ball.h"
#include "Map.h"
#include "GameState.h"

void Effects::looseLife()
{
	if (_balls.size() == 0)
	{
		_player.animateDeath();
		_lives.subtractLife();
		_balls.push_back(new Ball());
	}
}
void Effects::addEffect(int type, GameState & state)
{
	switch (type)
		/*
		0 - dodatkowe 2 kulki
		1 - sizeUpenie
		2 - pomniejszenie
		3 - przebijanie
		4 - strzelanie
		5 - ¿ycie
		6 - Floor
		7 - speedUp
		8 - speedDown
		9 - nic
		*/
	{
	case 0:
		//dodatkowe 2 kulki
		_balls.push_back(new Ball((*_balls.begin())->getPosition(), (*_balls.begin())->_speed, (*_balls.begin())->_state));
		_balls.push_back(new Ball((*_balls.begin())->getPosition(), (*_balls.begin())->_speed, (*_balls.begin())->_state));
		break;
	case 1:
		//sizeUpenie
		if (_effects[1] == 0)
		{
			if (_effects[2] == 0)
			{
				_player.sizeUp();
				_effects[1] += 450;
			}
			else
			{
				_effects[2] = 1;
			}
		}
		else
		{
			_effects[1] += 450;
		}
		break;
	case 2:
		//pomniejszenie
		if (_effects[2] == 0)
		{
			if (_effects[1] == 0)
			{
				_player.sizeDown();
				_effects[2] += 450;
			}
			else
			{
				_effects[1] = 1;
			}
		}
		else
		{
			_effects[2] += 450;
		}
		break;
	case 3:
		//przebijanie
		if (_effects[3] == 0)
		{
			for (Ball * el : _balls)
			{
				el->boost();
			}
			_effects[3] += 180;
		}
		else
		{
			_effects[3] += 180;
		}
		break;
	case 4:
		//strzelanie
		_ammo.addAmmo();
		break;
	case 5:
		//¿ycie
		_lives.addLife();
		break;
	case 6:
		//Floor
		_floor.add();
		break;
	case 7:
		//speedUp
		if (_effects[7] == 0)
		{
			if (_effects[8] == 0)
			{
				for (Ball * el : _balls)
				{
					el->speedUp();
				}
				_effects[7] += 300;
			}
			else
			{
				_effects[8] = 1;
			}
		}
		else
		{
			_effects[7] += 300;
		}
		break;
	case 8:
		//speedDown
		if (_effects[8] == 0)
		{
			if (_effects[7] == 0)
			{
				for (Ball * el : _balls)
				{
					el->speedDown();
				}
				_effects[8] += 300;
			}
			else
			{
				_effects[7] = 1;
			}
		}
		else
		{
			_effects[8] += 300;
		}
		break;
	}
}
void Effects::updateEffects(GameState & state)
{
	//sizeUpanie
	if (_effects[1] != 0)
	{
		_effects[1]--;
		if (_effects[1] == 0)
		{
			_player.sizeDown();
		}
	}
	//sizeDownanie
	if (_effects[2] != 0)
	{
		_effects[2]--;
		if (_effects[2] == 0)
		{
			_player.sizeUp();
		}
	}
	//przebijanie
	if (_effects[3] != 0)
	{
		_effects[3]--;
		for (Ball * el : _balls)
		{
			el->boost();
		}
		if (_effects[3] == 0)
		{
			for (Ball * el : _balls)
			{
				el->unboost();
			}
		}
	}
	//speedUp
	if (_effects[7] != 0)
	{
		_effects[7]--;
		for (Ball * el : _balls)
		{
			el->speedUp();
		}
		if (_effects[7] == 0)
		{
			for (Ball * el : _balls)
			{
				el->speedDown();
			}
		}
	}
	//speedDown
	if (_effects[8] != 0)
	{
		_effects[8]--;
		for (Ball * el : _balls)
		{
			el->speedDown();
		}
		if (_effects[8] == 0)
		{
			for (Ball * el : _balls)
			{
				el->speedUp();
			}
		}
	}
}
Effects::Effects(sf::Font & font) : _shooting(0)
{
	_lives.setFont(font);
	_balls.push_back(new Ball());
	_points.setFont(font);
	_ammo.setFont(font);
	_effects.resize(9);
	for (int el : _effects)
	{
		el = 0;
	}
	restartTempo();
}
Effects::~Effects()
{
	for (Ball * el : _balls)
	{
		delete el;
	}
}
void Effects::update(Map & map, GameState & state)
{
	//puls
	_pulseState++;
	if (_pulseState > 46.4) //46.4546099748370862636299116072 (60fps)
	{
		_pulseState -= 46.4;
		puls(map);
	}
	//strzelanie
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			_shooting++;
			if (_shooting == 6)
			{
				_shooting = 0;
				shoot(state);
			}
		}
	}
	//umieranie kulek
	for (std::list<Ball *>::iterator it = _balls.begin(); it != _balls.end();)
	{
		(*it)->execute(map, _player, _points, _floor, _pulseState, state);
		if ((*it)->_ifAlive == 0)
		{
			std::list<Ball *>::iterator it2 = it;
			it++;
			delete *it2;
			_balls.erase(it2);
			looseLife();
		}
		else
		{
			it++;
		}
	}
	//update pozosta³ych
	_player.execute(map._map, state);
	_points.update(_player);
	//dodawanie bonusów
	if (_points._bonusType != 9)
	{
		addEffect(_points._bonusType, state);
		_points._bonusType = 9;
	}
	//usuwanie bonusów
	updateEffects(state);
	//pora¿ka?
	if (_player._deathTime == 0)
	{
		_lives.ifPlayerDead(state);
	}
}
void Effects::puls(Map & Map)
{
	_points.subtractPoint();
	_player.explode();
	for (Ball * el : _balls)
	{
		el->Explosion(_player._deathTime);
	}
	Map.explode();
	_player.addPulse();
	for (Ball * el : _balls)
	{
		el->addPulse(_player._deathTime);
	}
}
void Effects::restartTempo()
{
	_pulseState = 0;
}
void Effects::shoot(GameState & state)
{
	if (_ammo.ifAnyAmmo())
	{
		_player.shoot();
		_ammo.subtractAmmo();
	}
}
void Effects::draw(sf::RenderWindow & window)
{
	_ammo.draw(window);
	_floor.draw(window);
	_player.draw(window);
	for (Ball * el : _balls)
	{
		el->draw(window, _player._deathTime);
	}
	_lives.draw(window);
	_points.draw(window);
}
void Effects::restart()
{
	for (Ball * el : _balls)
	{
		delete el;
	}
	_balls.clear();
	_balls.push_back(new Ball());
	_player.restart();
	_lives.restart();
	_points.restart();
	_ammo.restart();
	_floor.restart();
}
int Effects::getPoints()
{
	return _points.getPoints();
}