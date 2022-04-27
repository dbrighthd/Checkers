#pragma once
#include<SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <iostream>

#define Max_main_menu 3

class Menu
{
public:

	Menu(float width, float height);
	~Menu();
	void draw(sf::RenderWindow& window);
	void moveUp();
	void moveDown();
	void display_background(sf::RenderWindow& window);
	int option_selected()
	{
		return mainMenuSelected;
	}
	void instructions_text(sf::RenderWindow& window_play);
public:
	int mainMenuSelected;
	sf::Font font;
	sf::Text mainMenu[Max_main_menu];
};


