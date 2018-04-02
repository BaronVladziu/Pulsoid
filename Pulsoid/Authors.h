#pragma once
#include "header.h"
#include "Button.h"

class Authors
{
private:
	sf::Text _authors;
	std::vector<sf::Text> _vector;
	Button _ok;

	void addText(std::string & text, sf::Font & font, sf::Vector2f & position);
	void load(sf::Font & font);

public:
	Authors(sf::Font & font);
	void draw(sf::RenderWindow & window);
	void active(GameState & state);
};