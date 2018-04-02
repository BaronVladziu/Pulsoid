#pragma once
#include "header.h"

class Slider
{
private:
	sf::RectangleShape _center;
	sf::RectangleShape _outline;
	int _value;

public:
	Slider();
	void setPosition(sf::Vector2f & setPosition);
	void operator++();
	void operator--();
	void operator+(int val);
	void operator-(int val);
	int getValue();
	void setValue(int val);
	void draw(sf::RenderWindow & window);
};