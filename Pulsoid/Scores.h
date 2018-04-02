#pragma once
#include "header.h"
#include "Button.h"

class Scores
{
private:
	sf::Text _Scores;
	std::vector<sf::Text> _vector1;
	std::vector<sf::Text> _vector2;
	Button _ok;
	sf::RectangleShape _outline;
	sf::Font _font;
	sf::Text _playerName;

	void addText(std::string & text1, std::string & text2, sf::Font & font);
	void addText(std::string & text1, std::string & text2, sf::Font & font, bool czy);
	void load(sf::Font & font);
	void load(sf::Font & font, std::pair<std::string, int> & playerScore);
	void addAndSort(std::list<std::pair<std::string, int>> & list, const std::string & text, const int number);
	std::pair<std::string, int> addAndSort(std::list<std::pair<std::string, int>> & list, const std::string & text, const int number, bool czy);

public:
	int _fromWhere;
	/*
	0 - Menu
	1 - Pause
	2 - Scores
	*/
	bool _ifInRanking;

	Scores(sf::Font & font);
	void draw(sf::RenderWindow & window);
	void active(GameState & state);
	void win(int Points);
	void addSign(const char & znak);
	void removeSign();
};
