#pragma once
#include "header.h"

class Points
{
private:
	sf::Text _number;
	sf::Text _text;
	sf::Font _font;
	int _counter;
	std::list<Bonus *> _floatingBonuses;

public:
	int _bonusType;

	Points();
	~Points();
	void setFont(sf::Font & font);
	void addPoints(sf::Vector2f & position, bool boosted);
	void subtractPoint();
	void draw(sf::RenderWindow & window);
	void restart();
	void addBonus(sf::Vector2f & position, int type);
	void update(Player & player);
	int getPoints();
};