#include "Header.h"

Menu::Menu(float width, float height)
{
	// to check errors
	if (!font.loadFromFile("Assets/arial.ttf"))
	{
		// check error
	}

	            // Play option

	mainMenu[0].setFont(font);
	mainMenu[0].setFillColor(sf::Color::Blue);
	mainMenu[0].setString("PLAY");
	mainMenu[0].setCharacterSize(45);
	mainMenu[0].setPosition(sf::Vector2f(width / 2 - 60, height / (Max_main_menu + 1) * 1 ));

	           // Instructions option
	      
	mainMenu[1].setFont(font);
	mainMenu[1].setFillColor(sf::Color::Cyan);  
	mainMenu[1].setString("INSTRUCTIONS");
	mainMenu[1].setCharacterSize(45);
	//mainMenu[1].setPosition(sf::Vector2f(width / 2, height / (Max_main_menu + 1) * 2));
	mainMenu[1].setPosition(sf::Vector2f(width / 2 - 160, height / (Max_main_menu + 1) * 2));

	          // Exit option

	mainMenu[2].setFont(font);
	mainMenu[2].setFillColor(sf::Color::Cyan);  
	mainMenu[2].setString("EXIT");
	mainMenu[2].setCharacterSize(45);
	mainMenu[2].setPosition(sf::Vector2f(width / 2 - 80 , height / (Max_main_menu + 1) * 3));
	//mainMenu[2].setPosition(sf::Vector2f(width / 2 , height / (Max_main_menu + 1) * 3));

	mainMenuSelected = 0;

}

Menu::~Menu()
{
	// Nothing
}

void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < 3; i++)
	{
		window.draw(mainMenu[i]);
	}
}

void Menu::moveDown()
{
	if (mainMenuSelected + 1 <= Max_main_menu)  // Check if not on the last option (exit)
	{
		mainMenu[mainMenuSelected].setFillColor(sf::Color::Cyan);  // Change the previous option's color

		mainMenuSelected++;   // move to the lower option

		if (mainMenuSelected == 3)
		{
			mainMenuSelected = 0;
		}

		mainMenu[mainMenuSelected].setFillColor(sf::Color::Blue);   // change the new option color
	}
}

void Menu::moveUp()
{
	if (mainMenuSelected - 1 <= -1)   // Check if not on the first option (play)
	{
	
		mainMenu[mainMenuSelected].setFillColor(sf::Color::Cyan);   // Change the previous option's color

		mainMenuSelected--;  // move to the upper option

		if (mainMenuSelected == -1)
		{
			mainMenuSelected = 2;
		}

		mainMenu[mainMenuSelected].setFillColor(sf::Color::Blue);    // change the new  option color
	}
}

void Menu::display_background(sf::RenderWindow& window)
{
	
	        //Print the background
	sf::Texture texture;
	texture.loadFromFile("Assets/butchh.png");
	sf::Sprite image;
	image.setTexture(texture);
	//image.setScale(1.f, 1.f);
	image.setScale(0.5f, 0.4f);
	window.draw(image);

	     //Prints the title on the background 
	sf::Text text;
	text.setFont(font);
	text.setString("               Welcome to \n BUTCH'S CHECKERS GAME!\n");
	text.setCharacterSize(30);
	text.setFillColor(sf::Color::Yellow);
	text.setStyle(sf::Text::Bold);
	//text.setPosition(sf::Vector2f(30, 10));    // Might have to change
	text.setPosition(sf::Vector2f(25, 10));
	window.draw(text);

}

void Menu::instructions_text(sf::RenderWindow& window_play)
{

	sf::Texture texture;
	texture.loadFromFile("Assets/instruction.png");
	sf::Sprite image;
	image.setTexture(texture);
	image.setScale(0.5f, 0.7f);
	window_play.draw(image);

	/*sf::Text text;
	text.setFont(font);
	text.setString("HOW TO PLAY");
	text.setString("Choose a player to go first.On your turn, move any one of your checkers by");
	text.setString("the movement rules described below.After you move one checker, your turn is over.
	text.setString("	The game continues with players alternating turns.
		Movement Rules
		• Always move your checker diagonally forward, toward your opponent's side of the gameboard).
		Note: After a checker becomes a "King," it can move diagonally forward or backward.
		• Move your checker one space diagonally, to an open adjacent square; or jump one or more checkers
		diagonally to an open square adjacent to the checker you jumped.When you jump over an opponent's checker, 
		you capture it(see Capturing an Opponent's Checker).
			• If all squares adjacent to your checker are occupied, your checker is blockedand cannot move.
			Capturing an Opponent's Checker If you jump an opponent's checker, you capture it.
			Remove it from the gameboardand place it in front of you.
			Becoming a "King"
			As soon as one of your checkers reaches the first row on your opponent's side of the gameboard, 
			it becomes a King.Place another checker of the same color on top of it.
	text.setString("		Now this double - decker checker can move forward or backward on the gameboard.
	text.setString("HOW TO WIN");
	text.setString("The first player to capture all opposing checkers from the gameboard wins the game!");*/



}