#pragma once
#include "header.h"
#include "Player.h"

class Bonus
{
private:
	sf::CircleShape _outline;
	sf::Text _text;
	float _speed;

public:
	bool _ifAlive;
	bool _ifCatched;
	int _type;
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

	Bonus(sf::Vector2f & position, int type, sf::Font & font);
	void update(const Player & player);
	void draw(sf::RenderWindow & window);
};