
#include "Header.h"
#include <SFML/Audio.hpp>        // has been added
#include <SFML/Network.hpp>      // has been added

int page_number;

int main(void)
{
   while (true)   // We use that option because the exit section does not accept "break" in a for-loop
	{
		    // Initialize variables: 
		sf::RenderWindow window(sf::VideoMode(500, 500), "Checkers!", sf::Style::Close);

		Menu menu(500, 500);


		                          // Start of Audio functionality
		sf::Music music;
		if (!music.openFromFile("Assets/music.ogg"))
			return -1;   // error
		music.play();    // Play the audio 

		//music.setPlayingOffset(sf::seconds(60));
		//music.setVolume(15);

		//music.pause();  // pause playback
		//music.play();    // Play the music again
		//music.stop();  // stop playback and rewind
		    
		                         // End of audio functionality
								 


		cout << "You can only click down for the menu." << endl;
		cout << "If you reach the last option, when you click 'down', you will be redirected at the top." << endl;

		while (window.isOpen())
		{
			    sf::Event event;

			// Check if window needs to be closed: 
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}

				// Key has been released
				if (event.type == sf::Event::KeyReleased)
				{
					if (event.key.code == sf::Keyboard::Up)
					{
						menu.moveUp();
						break;
					}
					// You have to down for it to work, with use of actual keyboard, not a mouse
					if (event.key.code == sf::Keyboard::Down)
					{
						menu.moveDown();
						break;
					}

					    // Chosing pages: options

					if (event.key.code == sf::Keyboard::Return)
						// You have to press "enter" for it to work 
						// So use of actual keyboard, not a mouse

					{
						if (menu.option_selected() == 0)   // Play
						{
							window.close();
							page_number = 0;
						}

						if (menu.option_selected() == 1)   // Instructions
						{
							window.close();
							page_number = 1;
						}

						if (menu.option_selected() == 2)     // Exit
						{
							window.close();
							page_number = 2;
						}

					}

				}

			}

			  // Window commands: 
			window.clear();
			menu.display_background(window);
			menu.draw(window);
			window.display();

		}

		system("cls");  // Clear the screen

		                     // Effectuate the user input
		switch (page_number)
		{
			case 0:    // The game option
			{
				sf::RenderWindow window_play(sf::VideoMode(400, 400), "Play", sf::Style::Close);
				//cout << "  The section for 'play' has been selected!" << endl;
				while (window_play.isOpen())
				{
					sf::Event event;
					while (window_play.pollEvent(event))
					{
						if (event.type == sf::Event::Closed)
							window_play.close();
					}

					window_play.clear();
					
					     // adding the game loop
					game_loop();
					
					window_play.display();
				}

				break;
			}



			case 1:     // The instructions option

			{
				sf::RenderWindow window_play(sf::VideoMode(800, 800), "Instructions", sf::Style::Close);
				//cout << "  The section for 'instructions' has been selected!" << endl;
				while (window_play.isOpen())
				{
					sf::Event event;
					while (window_play.pollEvent(event))
					{
						if (event.type == sf::Event::Closed)
							window_play.close();
					}

					window_play.clear();

					    // Display the image for instructions
					menu.instructions_text(window_play);

					window_play.display();

				}

				break;

			}

			

		}  // end of the switch


			        // The exit option

		if (page_number == 2)
	      {

			  sf::RenderWindow window_play(sf::VideoMode(500, 500), "EXIT", sf::Style::Close);
			  while (window_play.isOpen())
			  {
				  sf::Event event;
				  while (window_play.pollEvent(event))
				  {
					  if (event.type == sf::Event::Closed)
						  window_play.close();
				  }

				  window_play.clear();

				     // Display the image for saying bye
				  menu.byeImage(window_play);

				  window_play.display();

			  }

			     // After closing the window, the message below appears and you exit

	   	      cout << "Thank you for passing by!" << endl << endl;
	   	      cout << "   Butch was happy to see you! " << endl;
			
	          break;
	      }


	}


	return 0;
} 



// Constructor: 
Board::Board()
{
	// Initialize variables: 
	double xTilePos = 0.0, yTilePos = 0.0;

	sf::Color redTile = sf::Color::Red;
	sf::Color blackTile = sf::Color::Black;

	// Draw board: 
	for (int i = 0; i < 8; ++i)
	{
		xTilePos = 0.0;
		for (int j = 0; j < 8; ++j)
		{
			if (i % 2 == 0)
			{
				if (j % 2 == 0)
				{
					this->mBoard[j][i].setColor(redTile);
				}

				else
				{
					this->mBoard[j][i].setColor(blackTile);
				}
			}

			else
			{
				if (j % 2 == 0)
				{
					this->mBoard[j][i].setColor(blackTile);
				}

				else
				{
					this->mBoard[j][i].setColor(redTile);
				}
			}

			this->mBoard[j][i].setPosition(xTilePos, yTilePos);
			xTilePos += 50;
		}

		yTilePos += 50;
	}

	// Set occupied: 

	// Intialize every slot to false: 
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			this->mOccupied[i][j] = false;
			this->mColor[i][j] = NO_TOKEN;
		}
	}

	// Set specific slots to true: 
	int k = 0;
	for (int i = 0; i < 3; i++)
	{
		if (i == 0 || i == 2)
		{
			for (int j = 0; j < 8; j += 2)
			{
				this->mOccupied[i][j] = true;
				this->mColor[i][j] = BLUE_PLAYER;
			}
		}

		else if (i == 1)
		{
			for (int j = 1; j < 8; j += 2)
			{
				this->mOccupied[i][j] = true;
				this->mColor[i][j] = BLUE_PLAYER;
			}
		}
	}

	// For the color blue

	k = 0;
	for (int i = 5; i < 8; i++)
	{
		if (i == 5 || i == 7)
		{
			for (int j = 1; j < 8; j += 2)
			{
				this->mOccupied[i][j] = true;
				this->mColor[i][j] = WHITE_PLAYER;
			}
		}

		else if (i == 6)
		{
			for (int j = 0; j < 8; j += 2)
			{
				this->mOccupied[i][j] = true;
				this->mColor[i][j] = WHITE_PLAYER;
			}
		}
	}
}


Tile Board::getTile(int i, int j)
{
	return this->mBoard[j][i];
}

bool Board::getOccupied(int i, int j)
{
	return this->mOccupied[j][i];
}

void Board::setOccupied(int i, int j)
{
	this->mOccupied[j][i] = true;
}

void Board::setNotOccupied(int i, int j)
{
	this->mOccupied[j][i] = false;
}

int Board::getColor(int i, int j)
{
	return this->mColor[j][i];
}

void Board::setColor(int i, int j, int color)
{
	this->mColor[j][i] = color;
}
