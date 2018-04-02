#pragma once
#include "header.h"
#include "Effects.h"
#include "Map.h"
#include "MainMenu.h"
#include "Pause.h"
#include "GameState.h"

int main()
{
	srand(int(time(NULL)));
	//do wczytywania plikow
	std::string text;
	char znak;
	int number;
	//³adowanie gry
	sf::Font font;
	font.loadFromFile("XPED.ttf");
	MainMenu MainMenu(font);
	Pause Pause(font);
	Effects Effects(font);
	//wczytywanie danych z pliku Map
	Map Map;
	//wczytywanie danych z pliku Options
	GameState state(font);
	std::fstream plik_opcji("Options.ini");
	while (!plik_opcji.eof())
	{
		plik_opcji >> text;
		if (text[0] != '/' || text[1] != '/')
		{
			plik_opcji >> znak;
			plik_opcji >> number;
			state.configure(text, number);
		}
	}
	plik_opcji.close();
	//ustawienia ekranu
	sf::ContextSettings settings;
	settings.antialiasingLevel = state._antialiasing;
	sf::RenderWindow window(sf::VideoMode(state._screenWidth, state._screenHeight), "Pulsoid", sf::Style::Default, settings);
	if (state._ifFullscreen == true)
	{
		sf::View view(window.getView());
		window.create(sf::VideoMode(state._screenWidth, state._screenHeight), "Pulsoid", sf::Style::Fullscreen, settings);
		window.setView(view);
	}
	//czas
	sf::Time time_diff = sf::microseconds(16667);
	sf::Time time;
	sf::Clock clock;
	//pêtelka
	while (window.isOpen())
	{
		time += clock.getElapsedTime();
		clock.restart();
		while (time > time_diff)
		{
			time -= time_diff;
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}
				switch (state._gameState)
				{
				case 0:
					//0 - menu g³ówne
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
					{
						MainMenu.down();
					}
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
					{
						MainMenu.up();
					}
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
					{
						MainMenu.active(window, state, Effects, Map);
					}
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
					{
						window.close();
					}
					break;
				case 1:
					//1 - gra
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
					{
						state.setGameStateToPause();
					}
					break;
				case 3:
					//3 - Options
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
					{
						state._Options.down();
					}
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
					{
						state._Options.up();
					}
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
					{
						state._Options.prop_right(state, settings);
					}
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
					{
						state._Options.prop_left(state, settings);
					}
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
					{
						state._Options.active(window, settings, state, Effects, Map);
					}
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
					{
						state._Options.esc(state);
					}
					break;
				case 4:
					//4 - Scores
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
					{
						state._Scores.active(state);
					}
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
					{
						state._Scores.active(state);
					}
					//obs³uga pisania
					if (state._Scores._ifInRanking == 1)
					{
						if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)
						{
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
							{
								state._Scores.addSign('Q');
							}
							else
							{
								state._Scores.addSign('q');
							}
						}
						if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W)
						{
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
							{
								state._Scores.addSign('W');
							}
							else
							{
								state._Scores.addSign('w');
							}
						}
						if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E)
						{
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
							{
								state._Scores.addSign('E');
							}
							else
							{
								state._Scores.addSign('e');
							}
						}
						if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
						{
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
							{
								state._Scores.addSign('R');
							}
							else
							{
								state._Scores.addSign('r');
							}
						}
						if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::T)
						{
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
							{
								state._Scores.addSign('T');
							}
							else
							{
								state._Scores.addSign('t');
							}
						}
						if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Y)
						{
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
							{
								state._Scores.addSign('Y');
							}
							else
							{
								state._Scores.addSign('y');
							}
						}
						if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::U)
						{
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
							{
								state._Scores.addSign('U');
							}
							else
							{
								state._Scores.addSign('u');
							}
						}
						if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::I)
						{
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
							{
								state._Scores.addSign('I');
							}
							else
							{
								state._Scores.addSign('i');
							}
						}
						if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::O)
						{
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
							{
								state._Scores.addSign('O');
							}
							else
							{
								state._Scores.addSign('o');
							}
						}
						if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
						{
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
							{
								state._Scores.addSign('P');
							}
							else
							{
								state._Scores.addSign('p');
							}
						}
						if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
						{
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
							{
								state._Scores.addSign('A');
							}
							else
							{
								state._Scores.addSign('a');
							}
						}
						if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
						{
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
							{
								state._Scores.addSign('S');
							}
							else
							{
								state._Scores.addSign('s');
							}
						}
						if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
						{
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
							{
								state._Scores.addSign('D');
							}
							else
							{
								state._Scores.addSign('d');
							}
						}
						if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F)
						{
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
							{
								state._Scores.addSign('F');
							}
							else
							{
								state._Scores.addSign('f');
							}
						}
						if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::G)
						{
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
							{
								state._Scores.addSign('G');
							}
							else
							{
								state._Scores.addSign('g');
							}
						}
						if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::H)
						{
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
							{
								state._Scores.addSign('H');
							}
							else
							{
								state._Scores.addSign('h');
							}
						}
						if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::J)
						{
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
							{
								state._Scores.addSign('J');
							}
							else
							{
								state._Scores.addSign('j');
							}
						}
						if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::K)
						{
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
							{
								state._Scores.addSign('K');
							}
							else
							{
								state._Scores.addSign('k');
							}
						}
						if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::L)
						{
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
							{
								state._Scores.addSign('L');
							}
							else
							{
								state._Scores.addSign('l');
							}
						}
						if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Z)
						{
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
							{
								state._Scores.addSign('Z');
							}
							else
							{
								state._Scores.addSign('z');
							}
						}
						if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::X)
						{
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
							{
								state._Scores.addSign('X');
							}
							else
							{
								state._Scores.addSign('x');
							}
						}
						if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::C)
						{
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
							{
								state._Scores.addSign('C');
							}
							else
							{
								state._Scores.addSign('c');
							}
						}
						if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::V)
						{
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
							{
								state._Scores.addSign('V');
							}
							else
							{
								state._Scores.addSign('v');
							}
						}
						if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::B)
						{
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
							{
								state._Scores.addSign('B');
							}
							else
							{
								state._Scores.addSign('b');
							}
						}
						if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::N)
						{
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
							{
								state._Scores.addSign('N');
							}
							else
							{
								state._Scores.addSign('n');
							}
						}
						if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M)
						{
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
							{
								state._Scores.addSign('M');
							}
							else
							{
								state._Scores.addSign('m');
							}
						}
						//usuwanie znaku
						if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace)
						{
							{
								state._Scores.removeSign();
							}
						}
					}
					break;
				case 5:
					//5 - Twórcy
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
					{
						state._authors.active(state);
					}
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
					{
						state.setGameStateToMenu();
					}
					break;
				case 6:
					//6 - Pause
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
					{
						Pause.down();
					}
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
					{
						Pause.up();
					}
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
					{
						Pause.active(window, state, Effects, Map);
					}
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
					{
						state.setGameStateToGame();
					}
					break;
				}
			}

			//aktualizacje
			switch (state._gameState)
			{
			case 0:
				MainMenu.update();
				break;
			case 1:
				Map.update(state, Effects.getPoints());
				Effects.update(Map, state);
				break;
			case 2:
				break;
			case 3:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					state._Options.Slider_right(state);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					state._Options.Slider_left(state);
				}
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			}
		}
		//wyœwietlanie
		window.clear();

		switch (state._gameState)
		{
		case 0:
			MainMenu.draw(window);
			break;
		case 1:
			Effects.draw(window);
			Map.draw(window);
			break;
		case 3:
			state._Options.draw(window);
			break;
		case 4:
			state._Scores.draw(window);
			break;
		case 5:
			state._authors.draw(window);
			break;
		case 6:
			Pause.draw(window);
			break;
		}

		window.display();
	} //while
	return 0;
}