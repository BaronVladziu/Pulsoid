#pragma once
#include "header.h"
#include "Brick.h"
#include "Ball.h"
#include "Map.h"
#include "Player.h"
#include "Floor.h"
#include "Points.h"
#include "GameState.h"

void Ball::keepEnergy()
{
	float a = (_speed / sqrt(pow(_velocity.x, 2) + pow(_velocity.y, 2)));
	_velocity.x *= a;
	_velocity.y *= a;
}
void Ball::destroy(Brick & el, std::list<Brick *> & map, Points & points, GameState & state)
{
	if (el.ifWillDie() && !_ifBoosted)
	{
		points.addPoints(sf::Vector2f(el.getPosition().x, el.getPosition().y), _ifBoosted);
	}
	el.destroy();
	_speed += 0.03f;
	keepEnergy();
}
void Ball::destroyBrick(std::list<Brick *> & Map, Points & Points, GameState & state)
{
	for (Brick * el : Map)
	{
		if (el->ifIsAlive())
		{
			//czy kolizja
			if (getPosition().x + 7 + _velocity.x > el->getPosition().x)
			{
				if (getPosition().x - 7 + _velocity.x < el->getPosition().x + 40)
				{
					if (getPosition().y + 7 + _velocity.y > el->getPosition().y)
					{
						if (getPosition().y - 7 + _velocity.y < el->getPosition().y + 15)
						{
							if (!_ifBoosted)
							{
								//reakcja kulki
								/*

								--| 1 | 2 | 3 |
								--|---|---|---|
								1 |   |   |   |
								--|---|---|---|
								2 |   | K |   |
								--|---|---|---|
								3 |   |   |   |
								--|---|---|---|

								\     /
								1\   /2

								4/   \3
								/     \

								*/
								//wiersz 1
								if (getPosition().y < el->getPosition().y)
								{
									//kolumna 1
									if (getPosition().x < el->getPosition().x)
									{
										if (_velocity.y > 0)
										{
											if (_velocity.x > 0)
											{
												//kierunek 1
												if (getPosition().y == el->getPosition().y)
												{
													_velocity.y *= -1;
												}
												if (abs(_velocity.x) / abs(_velocity.y) > abs(getPosition().x - el->getPosition().x) / abs(getPosition().y - el->getPosition().y))
												{
													_velocity.y *= -1;
												}
												else
												{
													_velocity.x *= -1;
												}
											}
											else
											{
												//kierunek 2
												_velocity.y *= -1;
											}
										}
										else
										{
											if (_velocity.x < 0)
											{
												//kierunek 3
											}
											else
											{
												//kierunek 4
												_velocity.x *= -1;
											}
										}
									}
									//kolumna 2
									else if (getPosition().x < el->getPosition().x + 40)
									{
										_velocity.y *= -1;
									}
									//kolumna 3
									else
									{
										if (_velocity.y > 0)
										{
											if (_velocity.x > 0)
											{
												//kierunek 1
												_velocity.y *= -1;
											}
											else
											{
												//kierunek 2
												if (getPosition().y == el->getPosition().y)
												{
													_velocity.y *= -1;
												}
												if (abs(_velocity.x) / abs(_velocity.y) > abs(getPosition().x - el->getPosition().x - 40) / abs(getPosition().y - el->getPosition().y))
												{
													_velocity.y *= -1;
												}
												else
												{
													_velocity.x *= -1;
												}
											}
										}
										else
										{
											if (_velocity.x < 0)
											{
												//kierunek 3
												_velocity.x *= -1;
											}
											else
											{
												//kierunek 4
											}
										}
									}
								}
								//wiersz 2
								else if (getPosition().y < el->getPosition().y + 15)
								{
									//kolumna 1
									if (getPosition().x < el->getPosition().x)
									{
										_velocity.x *= -1;
									}
									//kolumna 2
									else if (getPosition().x < el->getPosition().x + 40)
									{

									}
									//kolumna 3
									else
									{
										_velocity.x *= -1;
									}
								}
								//wiersz 3
								else
								{
									//kolumna 1
									if (getPosition().x < el->getPosition().x)
									{
										if (_velocity.y > 0)
										{
											if (_velocity.x > 0)
											{
												//kierunek 1
												_velocity.x *= -1;
											}
											else
											{
												//kierunek 2
											}
										}
										else
										{
											if (_velocity.x < 0)
											{
												//kierunek 3
												_velocity.y *= -1;
											}
											else
											{
												//kierunek 4
												if (getPosition().y == el->getPosition().y)
												{
													_velocity.y *= -1;
												}
												if (abs(_velocity.x) / abs(_velocity.y) > abs(getPosition().x - el->getPosition().x) / abs(getPosition().y - el->getPosition().y - 15))
												{
													_velocity.y *= -1;
												}
												else
												{
													_velocity.x *= -1;
												}
											}
										}
									}
									//kolumna 2
									else if (getPosition().x < el->getPosition().x + 40)
									{
										_velocity.y *= -1;
									}
									//kolumna 3
									else
									{
										if (_velocity.y > 0)
										{
											if (_velocity.x > 0)
											{
												//kierunek 1
											}
											else
											{
												//kierunek 2
												_velocity.x *= -1;
											}
										}
										else
										{
											if (_velocity.x < 0)
											{
												//kierunek 3
												if (getPosition().y == el->getPosition().y)
												{
													_velocity.y *= -1;
												}
												if (abs(_velocity.x) / abs(_velocity.y) > abs(getPosition().x - el->getPosition().x - 40) / abs(getPosition().y - el->getPosition().y - 15))
												{
													_velocity.y *= -1;
												}
												else
												{
													_velocity.x *= -1;
												}
											}
											else
											{
												//kierunek 4
												_velocity.y *= -1;
											}
										}
									}
								}
							}
							destroy(*el, Map, Points, state);
						}
					}
				}
			}
			keepEnergy();
		}
	}
}
Ball::Ball()
	: _velocity(1, -5), _speed(4), _pause(120), _ifAlive(1), _ifBoosted(0), _state(2), _explosionTime(0)
{
	setRadius(5);
	setOrigin(5, 5);
	setPosition(400, 400);
	setFillColor(sf::Color::Black);
	setOutlineThickness(4);
	setOutlineColor(sf::Color::White);
	keepEnergy();
}
Ball::Ball(const sf::Vector2f & position, float speed, int state)
	: _velocity(float(rand() % 11 - 5),float(-(rand() % 5) - 2)), _speed(speed), _pause(0), _ifAlive(true), _ifBoosted(false), _state(state), _explosionTime(0)
{
	setRadius(5);
	setOrigin(5, 5);
	setPosition(position);
	setFillColor(sf::Color::Black);
	setOutlineThickness(4);
	setOutlineColor(sf::Color::White);
	keepEnergy();
}
void Ball::Explosion(int _deathTime)
{
	if (_deathTime == 0)
	{
		_explosionTime = 10;
		setOrigin(getOrigin() + sf::Vector2f(float(_explosionTime), float(_explosionTime)));
		setRadius(getRadius() + (_explosionTime));
	}
}
void Ball::addPulse(int _deathTime)
{
	if (_deathTime == 0)
	{
		_pulse.addPulse(getPosition(), getRadius(), getOrigin());
	}
}
void Ball::speedUp()
{
	if (_state < 3)
	{
		_speed += 2;
		keepEnergy();
		_state++;
	}
}
void Ball::speedDown()
{
	if (_state > 1)
	{
		_speed -= 2;
		keepEnergy();
		_state--;
	}
}
void Ball::boost()
{
	_ifBoosted = true;
	setFillColor(sf::Color::White);
}
void Ball::unboost()
{
	_ifBoosted = false;
	setFillColor(sf::Color::Black);
}
void Ball::execute(Map & map, const Player & player, Points & points, Floor & floor, const long double & pulseState, GameState & state)
{
	//puls
	_pulse.update(getPosition(), getRadius(), getOrigin(), pulseState);
	if (_explosionTime != 0)
	{
		_explosionTime--;
		setOrigin(getOrigin() - sf::Vector2f(1, 1));
		setRadius(getRadius() - 1);
	}
	if (_pause != 0)
	{
		_pause--;
	}
	else
	{
		//Trail kulki
		_ballTrail.update(getPosition(), _speed, _velocity);
		//blokowanie moveu poziomego
		if (_velocity.y == 0)
		{
			_velocity.y = 1;
			keepEnergy();
		}
		//kolizje œcian
		if (getPosition().x + _velocity.x + 7 > 800 || getPosition().x + _velocity.x - 7 < 0)
		{
			_velocity.x *= -1;
		}
		if (getPosition().y + _velocity.y - 7 < 0)
		{
			_velocity.y *= -1;
		}
		if (getPosition().y + _velocity.y + 7 > 650)
		{
			//_velocity.y *= -1; //niewidzialna Floor
			_ifAlive = 0;
		}
		//kolizje z pod³og¹
		if (getPosition().y + _velocity.y > floor.getPosition().y && getPosition().y + _velocity.y < floor.getPosition().y + floor.getSize().y)
		{
			if (floor.ifIsAlive())
			{
				_velocity.y *= -1;
				floor.subtract();
			}
		}
		//kolizje z p³ytkami
		destroyBrick(map._map, points, state);
		//kolizje z graczem
		if (getPosition().y + _velocity.y + 7 > player.getPosition().y && getPosition().y + _velocity.y - 7 < player.getPosition().y + 10)
		{
			float distance = getPosition().x + _velocity.x - player.getPosition().x - 4 - 6;
			if (distance > -((player.getSize().x + 4) / 2) - 7 && distance < (player.getSize().x + 4) / 2 + 7)
			{
				setPosition(getPosition().x, player.getPosition().y - 7);
				_velocity.x = distance * 10 / player.getSize().x;
				_velocity.y *= -1;
				keepEnergy();
			}
			keepEnergy();
		}
		//wreszcie move
		move(_velocity);
		//wypychanie ze œcian
		if (getPosition().x - 7 < 0)
		{
			setPosition(7, getPosition().y);
		}
		else if (getPosition().x + 7 > 800)
		{
			setPosition(793, getPosition().y);
		}
	}
}
void Ball::draw(sf::RenderWindow & window, int _deathTime)
{
	_pulse.draw(window);
	_ballTrail.draw(window);
	if (_deathTime == 0)
	{
		window.draw(*this);
	}
}