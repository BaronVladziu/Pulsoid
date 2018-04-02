#pragma once
#include "header.h"
#include "Slider.h"
#include "Stamp.h"

class Options
{
private:
	sf::Text _Options;
	std::vector<Button *> _vector;
	/*
	0 - Music Volume
	1 - Screen Proportions
	2 - Fullscreen
	3 - Back
	*/
	int _active;
	bool _ifChange;

	void change();

public:
	std::vector<Button *> _proportions;
	/*
	0 - 4 : 3 (16 : 12)
	1 - 16 : 10
	2 - 16 : 9
	*/
	int _propVal;
	bool _fromWhere;
	/*
	0 - Menu
	1 - Pause
	*/
	Stamp _StampF;
	Slider _SliderA;
	Slider _SliderMUZ;

	Options(sf::Font & font);
	~Options();
	void draw(sf::RenderWindow & window);
	void up();
	void down();
	void active(sf::RenderWindow & window, sf::ContextSettings & settings, GameState & state, Effects & effects, Map & map);
	void Slider_right(GameState & state);
	void Slider_left(GameState & state);
	void prop_right(GameState & state, sf::ContextSettings & settings);
	void prop_left(GameState & state, sf::ContextSettings & settings);
	void esc(GameState & state);
};