#pragma once
#include "header.h"
#include "Button.h"

class Instruction
{
private:
	sf::Text _instruction;
	std::vector<sf::Text> _vector;
	Button _ok;

	void addText(std::string & text, sf::Font & font, sf::Vector2f & position);
	void load(sf::Font & font);

public:
	int _fromWhere;
	/*

	*/

	Instruction(sf::Font & font);
	void draw(sf::RenderWindow & window);
	void active(GameState & state);
	void esc(GameState & state);
};