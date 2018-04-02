#pragma once
#include "header.h"

class Button
{
private:
	sf::Text _text;
	sf::RectangleShape _outline;

public:
	bool _ifActive;

	Button(sf::Font & font);
	void setString(std::string & text);
	void setSize(sf::Vector2f & size);
	void setPosition(sf::Vector2f & setPosition);
	void update();
	void draw(sf::RenderWindow & window);
};