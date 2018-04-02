#pragma once
#include "header.h"

class Floor
	: public sf::RectangleShape
{
private:
	int _counter;

public:
	Floor();
	bool ifIsAlive();
	void add();
	void subtract();
	void draw(sf::RenderWindow & window);
	void restart();
};