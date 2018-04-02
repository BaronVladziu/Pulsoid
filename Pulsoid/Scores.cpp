#pragma once
#include "header.h"
#include "Points.h"
#include "GameState.h"
#include "Scores.h"

void Scores::addText(std::string & text1, std::string & text2, sf::Font & font)
{
	sf::Text tekst;
	tekst.setFillColor(sf::Color::White);
	tekst.setFont(font);
	tekst.setCharacterSize(18);
	tekst.setPosition(250, _vector1.size() * 25.f + 100);
	tekst.setString(text1);
	_vector1.push_back(tekst);
	tekst.setPosition(400, _vector2.size() * 25.f + 100);
	tekst.setString(text2);
	_vector2.push_back(tekst);
}
void Scores::addText(std::string & text1, std::string & text2, sf::Font & font, bool czy)
{
	_outline.setPosition(240, _vector1.size() * 25.f + 104);
	_playerName.setPosition(250, _vector1.size() * 25.f + 100);
	sf::Text tekst;
	tekst.setFillColor(sf::Color::White);
	tekst.setFont(font);
	tekst.setCharacterSize(18);
	tekst.setPosition(250, _vector1.size() * 25.f + 100);
	tekst.setString(text1);
	_vector1.push_back(tekst);
	tekst.setPosition(400, _vector2.size() * 25.f + 100);
	tekst.setString(text2);
	_vector2.push_back(tekst);
}
void Scores::load(sf::Font & font)
{
	_vector1.clear();
	_vector2.clear();
	addText(std::string("Player"), std::string("Points"), font);
	std::string text1;
	std::string text2;
	std::fstream plik;
	plik.open("scores.dat");
	while (!plik.eof())
	{
		plik >> text1;
		plik >> text2;
		addText(text1, text2, font);
	}
	plik.close();
}
void Scores::load(sf::Font & font, std::pair<std::string, int> & playerScore)
{
	_vector1.clear();
	_vector2.clear();
	addText(std::string("Player"), std::string("Points"), font);
	std::string text1;
	int text2;
	std::fstream plik;
	plik.open("scores.dat");
	while (!plik.eof())
	{
		plik >> text1;
		plik >> text2;
		if (playerScore.second == text2)
		{
			if (playerScore.first == text1)
			{
				addText(text1, std::to_string(text2), font, 0);
			}
		}
		else
		{
			addText(text1, std::to_string(text2), font);
		}
	}
	plik.close();
}
Scores::Scores(sf::Font & font) : _ok(font), _font(font), _ifInRanking(0)
{
	_Scores.setCharacterSize(48);
	_Scores.setFillColor(sf::Color::White);
	_Scores.setStyle(sf::Text::Regular);
	_Scores.setFont(font);
	_Scores.setPosition(300, 20);
	_Scores.setString("Scores");
	_playerName.setFillColor(sf::Color::White);
	_playerName.setFont(font);
	_playerName.setCharacterSize(18);
	load(font);
	_ok.setPosition(sf::Vector2f(60, 390));
	_ok.setString(std::string("Back"));
	_ok._ifActive = 1;
	_outline.setFillColor(sf::Color::Transparent);
	_outline.setOutlineColor(sf::Color::White);
	_outline.setOutlineThickness(4);
	_outline.setSize(sf::Vector2f(250, 19));
}
void Scores::draw(sf::RenderWindow & window)
{
	_ok.draw(window);
	window.draw(_Scores);
	for (sf::Text & el : _vector1)
	{
		window.draw(el);
	}
	for (sf::Text & el : _vector2)
	{
		window.draw(el);
	}
	if (_ifInRanking == 1)
	{
		window.draw(_outline);
		window.draw(_playerName);
	}
}
void Scores::active(GameState & state)
{
	switch (_fromWhere)
	{
	case 0:
		state.setGameStateToMenu();
		break;
	case 1:
		state.setGameStateToPause();
		break;
	case 2:
		//restart nazwy
		_Scores.setString(std::string("Scores"));
		_Scores.move(100, 0);
		if (_ifInRanking == 1)
		{
			//wczytanie wyników
			int nr_wyniku = int((_playerName.getPosition().y - 100.f) / 25.f);
			std::string text;
			int number;
			std::list<std::pair<std::string, int>> list;
			std::fstream plik;
			plik.open("scores.dat");
			while (!plik.eof())
			{
				plik >> text;
				plik >> number;
				//zapisanie nazwy gracza
				if (nr_wyniku == 1)
				{
					if (_playerName.getString() == "")
					{
						_playerName.setString("noname");
					}
					text = _playerName.getString();
				}
				nr_wyniku--;
				//sortowanie
				addAndSort(list, text, number);
			}
			plik.close();
			//zapisanie wyników
			std::ofstream usuwanie_pliku;
			usuwanie_pliku.open("scores.dat", std::ios_base::trunc);
			usuwanie_pliku.close();
			plik.open("scores.dat");
			for (std::pair<std::string, int> el : list)
			{
				plik << std::endl;
				plik << el.first << " " << el.second;
			}
			plik.close();
			//update
			load(_font);
			_ifInRanking = 0;
		}
		//state
		state.setGameStateToScores(0, 0);
		break;
	}
}
void Scores::win(int Points)
{
	_Scores.setString(std::string("YOU WON"));
	_Scores.move(-100, 0);
	//zapisywanie wyników
	//wczytywanie
	std::string text;
	int number;
	std::list<std::pair<std::string, int>> list;
	std::fstream plik;
	plik.open("scores.dat");
	while (!plik.eof())
	{
		plik >> text;
		plik >> number;
		//sortowanie
		addAndSort(list, text, number);
	}
	plik.close();
	std::pair<std::string, int> playerScore;
	//czy adde siê do rankingu
	if ((--list.end())->second < Points)
	{
		_ifInRanking = 1;
		//dodanie wyniku gracza
		playerScore = addAndSort(list, "œ", Points, 0);
		//usuwanie nadmiaru wyników
		while (list.size() > 10)
		{
			list.pop_back();
		}
		//zapisywanie
		std::ofstream usuwanie_pliku;
		usuwanie_pliku.open("scores.dat", std::ios_base::trunc);
		usuwanie_pliku.close();
		plik.open("scores.dat");
		for (std::pair<std::string, int> el : list)
		{
			plik << std::endl;
			plik << el.first << " " << el.second;
		}
		plik.close();
		//update
		load(_font, playerScore);
	}
}
void Scores::addAndSort(std::list<std::pair<std::string, int>> & list, const std::string & text, const int number)
{
	if (list.empty())
	{
		std::pair<std::string, int> para(text, number);
		list.insert(list.begin(), para);
	}
	else
	{
		for (std::list<std::pair<std::string, int>>::iterator it = list.begin(); it != list.end();)
		{
			if (it->second < number)
			{
				std::pair<std::string, int> para(text, number);
				list.insert(it, para);
				break;
			}
			else if (++it == list.end())
			{
				std::pair<std::string, int> para(text, number);
				list.insert(it, para);
			}
		}
	}
}
std::pair<std::string, int> Scores::addAndSort(std::list<std::pair<std::string, int>> & list, const std::string & text, const int number, bool czy)
{
	std::pair<std::string, int> pair;
	pair.first = text;
	pair.second = number;
	if (list.empty())
	{
		list.insert(list.begin(), pair);
	}
	else
	{
		for (std::list<std::pair<std::string, int>>::iterator it = list.begin(); it != list.end();)
		{
			if (it->second < number)
			{
				list.insert(it, pair);
				return pair;
			}
			else if (++it == list.end())
			{
				list.insert(it, pair);
			}
		}
	}
	return pair;
}
void Scores::addSign(const char & znak)
{
	std::string text = _playerName.getString().toAnsiString();
	if (text.size() < 10)
	{
		text.push_back(znak);
		_playerName.setString(text);
	}
}
void Scores::removeSign()
{
	std::string text = _playerName.getString().toAnsiString();
	if (text.size() > 0)
	{
		text.pop_back();
		_playerName.setString(text);
	}
}