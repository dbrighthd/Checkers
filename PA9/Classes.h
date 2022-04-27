#ifndef Classes



#include<SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <iostream>

using std::cout;
using std::endl;

#define BLUE_PLAYER 0
#define WHITE_PLAYER 1
#define NO_TOKEN 2
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

class Tile : public sf::RectangleShape
{
public:
	Tile(const sf::Vector2f& pos = sf::Vector2f(0, 0), const sf::Vector2f& size = sf::Vector2f(50, 50), const sf::Color& color = sf::Color::Black) :
		sf::RectangleShape(size)
	{
		this->setFillColor(color);
		this->setPosition(pos);
		this->setSize(size);
	}

	void setColor(sf::Color& color);
	void setPos(sf::Vector2f& pos);
};

class Token : public sf::CircleShape
{
private:
	bool mIsActive;
	double mXPos;
	double mYPos;



public:


	Token(const sf::Vector2f& pos = sf::Vector2f(25, 25), const double& radius = 15, const sf::Color& color = sf::Color::White) :
		sf::CircleShape(radius)
	{
		this->setPosition(pos);
		this->setRadius(radius);
		this->setFillColor(color);
	}

	void setNewFillColor(sf::Color newColor);

	double getXLocation(void);
	double getYLocation(void);

	void setXLocation(double newXLocation);
	void setYLocation(double newYLocation);


};

class Board
{
private:
	Tile mBoard[8][8];
	bool mOccupied[8][8];
	int mColor[8][8];

public:
	Board();
	Tile getTile(int i, int j);
	bool getOccupied(int i, int j);
	void setOccupied(int i, int j);
	void setNotOccupied(int i, int j);
	int getColor(int i, int j);
	void setColor(int i, int j, int color);
};

#endif // !Classes