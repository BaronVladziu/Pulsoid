#pragma once
#include "header.h"

class Ammo
{
private:
	sf::Text _number;
	sf::Text _text;
	int _counter;

public:
	Ammo();
	void setFont(sf::Font & font);
	void addAmmo();
	void subtractAmmo();
	void draw(sf::RenderWindow & window);
	bool ifAnyAmmo();
	void restart();
};