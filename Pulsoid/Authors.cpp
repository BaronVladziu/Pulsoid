#pragma once
#include "header.h"
#include "GameState.h"
#include "Authors.h"

void Authors::addText(std::string & text, sf::Font & font, sf::Vector2f & position)
{
	sf::Text tekst;
	tekst.setFillColor(sf::Color::White);
	tekst.setFont(font);
	tekst.setCharacterSize(12);
	tekst.setString(text);
	if (position.x + tekst.getLocalBounds().width > 700)
	{
		position.x = 100;
		position.y += 12;
		tekst.setPosition(position);
	}
	else
	{
		tekst.setPosition(position);
		position.x += tekst.getLocalBounds().width + 15;
	}
	_vector.push_back(tekst);
}
void Authors::load(sf::Font & font)
{
	sf::Vector2f position = sf::Vector2f(100, 80);
	std::string text;
	std::fstream plik;
	plik.open("authors.dat");
	while (!plik.eof())
	{
		plik >> text;
		if (text == "/")
		{
			position.x = 100;
			position.y += 12;
		}
		else
		{
			addText(text, font, position);
		}
	}
	plik.close();
}
Authors::Authors(sf::Font & font) : _ok(font)
{
	_authors.setCharacterSize(48);
	_authors.setFillColor(sf::Color::White);
	_authors.setStyle(sf::Text::Regular);
	_authors.setFont(font);
	_authors.setPosition(300, 20);
	_authors.setString("Authors");
	load(font);
	_ok.setPosition(sf::Vector2f(60, 390));
	_ok.setString(std::string("Back"));
	_ok._ifActive = 1;
}
void Authors::draw(sf::RenderWindow & window)
{
	_ok.draw(window);
	window.draw(_authors);
	for (sf::Text & el : _vector)
	{
		window.draw(el);
	}
}
void Authors::active(GameState & state)
{
	state.setGameStateToMenu();
}