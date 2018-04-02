#pragma once
#include "header.h"
#include "Instruction.h"
#include "GameState.h"

void Instruction::addText(std::string & text, sf::Font & font, sf::Vector2f & position)
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
void Instruction::load(sf::Font & font)
{
	sf::Vector2f position = sf::Vector2f(100, 80);
	std::string text;
	std::fstream plik;
	plik.open("instruction.dat");
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
Instruction::Instruction(sf::Font & font) : _ok(font), _fromWhere(0)
{
	_instruction.setCharacterSize(48);
	_instruction.setFillColor(sf::Color::White);
	_instruction.setStyle(sf::Text::Regular);
	_instruction.setFont(font);
	_instruction.setPosition(250, 20);
	_instruction.setString("Instruction");
	load(font);
	_ok.setPosition(sf::Vector2f(60, 390));
	_ok.setString(std::string("Back"));
	_ok._ifActive = 1;
}
void Instruction::draw(sf::RenderWindow & window)
{
	_ok.draw(window);
	window.draw(_instruction);
	for (sf::Text & el : _vector)
	{
		window.draw(el);
	}
}
void Instruction::active(GameState & state)
{
	state.setGameStateToMenu();
}
void Instruction::esc(GameState & state)
{
	state.setGameStateToMenu();
}