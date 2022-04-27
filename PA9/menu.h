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

	       // This function displays the background image and text 
	void display_background(sf::RenderWindow& window);

	           // This function accessed the menu selected by the user
	int option_selected()
	{
		return mainMenuSelected;
	}

	     // This function shows the image for the instructions of the game
	void instructions_text(sf::RenderWindow& window_play);

	    // This function displays an image for saying bye
	void byeImage(sf::RenderWindow& window_play);

public:

	int mainMenuSelected;
	sf::Font font;
	sf::Text mainMenu[Max_main_menu];


};


