#include "Header.h"

void game_loop()
{
	// Initialize variables: 
	sf::RenderWindow window(sf::VideoMode(400, 400), "Checkers!");
	Board gameBoard;
	sf::Color redTile = sf::Color::Red;
	sf::Color blackTile = sf::Color::Black;
	sf::Color active = sf::Color::Yellow;
	double xPos = 0.0, yPos = 0.0;
	bool occupiedTest = false;
	Token BluePieces[12];
	Token WhitePieces[12];
	double xTokenPos = 10, yTokenPos = 10;

	// Set player turn: 
	int playerTurn = BLUE_PLAYER;

	// Number of token of each player
	int blue_num_token = 12;
	int white_num_token = 12;


	// Set blue piece location: 
	for (int i = 0; i < 12; ++i)
	{
		// Set location: 
		BluePieces[i].setPosition(xTokenPos, yTokenPos);
		BluePieces[i].setXLocation(xTokenPos);
		BluePieces[i].setYLocation(yTokenPos);

		// Move X location: 
		xTokenPos += 100.0;

		// If reaching maximum: 
		if ((i + 1) % 4 == 0)
		{
			// Move back to start of row; 
			xTokenPos = 10;

			if ((i + 1) == 4)
			{
				// Offset tokens: 
				xTokenPos = 60;
			}

			// Move to next row: 
			yTokenPos += 50.0;
		}
	}

	// Set token position for tokens on other side of board: 
	yTokenPos = 260, xTokenPos = 60;

	// Set white piece location: 
	for (int i = 0; i < 12; ++i)
	{
		// Set location: 
		WhitePieces[i].setPosition(xTokenPos, yTokenPos);
		WhitePieces[i].setXLocation(xTokenPos);
		WhitePieces[i].setYLocation(yTokenPos);

		// Move X Location: 
		xTokenPos += 100;

		if ((i + 1) % 4 == 0)
		{
			// Move back to start of row: 
			xTokenPos = 60;

			if ((i + 1) == 4)
			{
				// Offset for middle row: 
				xTokenPos = 10;
			}

			// Move to next row: 
			yTokenPos += 50;
		}
	}

	// Set piece color: 
	for (int i = 0; i < 12; i++)
	{
		BluePieces[i].setFillColor(sf::Color::Blue);
		WhitePieces[i].setFillColor(sf::Color::White);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Infinite loop: 
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
		}

		// Blue player turn: 
		if (playerTurn == BLUE_PLAYER)
		{
			//cout << "Blue Player's Turn!" << endl; 
			bool moveOn = false;

			if (event.type == sf::Event::MouseButtonReleased)
			{
				// Get position of click: 
				xPos = sf::Mouse::getPosition(window).x;
				yPos = sf::Mouse::getPosition(window).y;

				int vectRow = 0, vectCol = 0;
				bool firstRun = true;
				bool myTurn = true;
				int dummyX2 = 30, dummyY2 = 30;

				// Set array values: 
				vectRow = yPos / 50;
				vectCol = xPos / 50;

				// Check if user clicked a specific token: 
				for (int i = 0; i < 12; ++i)
				{
					int dummyX = int(BluePieces[i].getXLocation()) / 50;
					int dummyY = int(BluePieces[i].getYLocation()) / 50;

					// Check for clicking: 
					if (vectRow == dummyY && vectCol == dummyX)
					{
						int deselect = 0;
						// Change to active color: 
						BluePieces[i].setFillColor(active);

						// Draw game board: 
						drawBoard(window, gameBoard, BluePieces, WhitePieces);

						// Get another click from the user: 
						while (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
						{
							;
						}
						
						while (moveOn == false)
						{
							if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
							{
								// Get second click location: 
								xPos = sf::Mouse::getPosition(window).x;
								yPos = sf::Mouse::getPosition(window).y;

								dummyX2 = xPos / 50;
								dummyY2 = yPos / 50;

								// Check if piece can be moved normally: 
								if ((dummyX == dummyX2 - 1) && (dummyY == dummyY2 - 1))
								{
									moveOn = moveNormal1(gameBoard, dummyX, dummyX2, dummyY, dummyY2, BluePieces[i]);
								}
								if ((dummyX == dummyX2 + 1) && (dummyY == dummyY2 - 1))
								{
									moveOn = moveNormal2(gameBoard, dummyX, dummyX2, dummyY, dummyY2, BluePieces[i]);
								}

								// Check if piece is attacking: 
								if ((dummyX == dummyX2 - 2) && (dummyY == dummyY2 - 2))
								{
									moveOn = attack1(gameBoard, dummyX, dummyX2, dummyY, dummyY2, BluePieces[i],
										WhitePieces);
									// Decrementing the number of token after being captured
									white_num_token--;
								}
								if ((dummyX == dummyX2 + 2) && (dummyY == dummyY2 - 2))
								{
									moveOn = attack2(gameBoard, dummyX, dummyX2, dummyY, dummyY2, BluePieces[i],
										WhitePieces);
									// Decrementing the number of token after being captured
									white_num_token--;
								}

								// Check if piece is a king and moves backwards normally: 
								if ((dummyX == dummyX2 + 1) && (dummyY == dummyY2 + 1) && BluePieces[i].checkKing())
								{
									moveOn = kingMoveNormal1(gameBoard, dummyX, dummyX2, dummyY, dummyY2,
										BluePieces[i]);

								}
								if ((dummyX == dummyX2 - 1) && (dummyY = dummyY2 + 1) && BluePieces[i].checkKing())
								{
									moveOn = kingMoveNormal2(gameBoard, dummyX, dummyX2, dummyY, dummyY2,
										BluePieces[i]);
								}

								// Check if piece is a king and attacks: 
								if ((dummyX == dummyX2 + 2) && (dummyY == dummyY2 + 2) && BluePieces[i].checkKing())
								{
									moveOn = kingAttack1(gameBoard, dummyX, dummyX2, dummyY, dummyY2,
										BluePieces[i], WhitePieces);
									// Decrementing the number of token after being captured
									white_num_token--;
								}

								if ((dummyX == dummyX2 - 2) && (dummyY == dummyY2 + 2) && BluePieces[i].checkKing())
								{
									moveOn = kingAttack2(gameBoard, dummyX, dummyX2, dummyY, dummyY2,
										BluePieces[i], WhitePieces);
									// Decrementing the number of token after being captured
									white_num_token--;
								}

								// Deselecting piece: 
								else
								{
									 if (BluePieces[i].getFillColor() == active)
									 {
										 deselect = 1;
										 if (BluePieces[i].checkKing())
										 {
											 BluePieces[i].setFillColor(sf::Color::Cyan);
										 }

										 else
										 {
											 BluePieces[i].setFillColor(sf::Color::Blue);

										 }
										 break;
									 }
									
								}
							}

							//cout << dummyX2 << " " << dummyY2 << endl;
						}

						

						// Switch user:
						if (deselect == 0)
						{
							cout << "Ended" << endl;
							playerTurn = WHITE_PLAYER;
						}
					}
				}
			}

		}

		// White Player's turn: 
		if (playerTurn == WHITE_PLAYER)
		{
			//cout << "Blue Player's Turn!" << endl;
			bool moveOn = false;

			if (event.type == sf::Event::MouseButtonReleased)
			{
				// Get position of click: 
				xPos = sf::Mouse::getPosition(window).x;
				yPos = sf::Mouse::getPosition(window).y;

				int vectRow = 0, vectCol = 0;
				bool firstRun = true;
				int dummyX2 = 30, dummyY2 = 30;

				// Set array values: 
				vectRow = yPos / 50;
				vectCol = xPos / 50;

				// Check if user clicked a specific token: 
				for (int i = 0; i < 12; ++i)
				{
					int dummyX = int(WhitePieces[i].getXLocation()) / 50;
					int dummyY = int(WhitePieces[i].getYLocation()) / 50;

					// Check for clicking: 
					if (vectRow == dummyY && vectCol == dummyX)
					{
						int deselect = 0;
						// Change fill color: 
						WhitePieces[i].setFillColor(active);

						// Draw game board: 
						drawBoard(window, gameBoard, BluePieces, WhitePieces);

						// Get another click from the user: 
						while (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
						{
							;
						}

						while (moveOn == false)
						{
							if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
							{
								// Get second click location: 
								xPos = sf::Mouse::getPosition(window).x;
								yPos = sf::Mouse::getPosition(window).y;

								dummyX2 = xPos / 50;
								dummyY2 = yPos / 50;

								// Check if piece can be moved normally: 
								if ((dummyX == dummyX2 + 1) && (dummyY == dummyY2 + 1))
								{
									moveOn = moveNormalWhite1(gameBoard, dummyX, dummyX2, dummyY, dummyY2,
										WhitePieces[i]);
								}

								if ((dummyX == dummyX2 - 1) && (dummyY == dummyY2 + 1))
								{
									moveOn = moveNormalWhite2(gameBoard, dummyX, dummyX2, dummyY, dummyY2,
										WhitePieces[i]);
								}

								// Check if piece can attack: 
								if ((dummyX == dummyX2 + 2) && (dummyY == dummyY2 + 2))
								{
									moveOn = attackWhite1(gameBoard, dummyX, dummyX2, dummyY, dummyY2, WhitePieces[i],
										BluePieces);
									// Decrementing the number of token after being captured
									blue_num_token--;
								}

								if ((dummyX == dummyX2 - 2) && (dummyY == dummyY2 + 2))
								{
									moveOn = attackWhite2(gameBoard, dummyX, dummyX2, dummyY, dummyY2, WhitePieces[i],
										BluePieces);
									// Decrementing the number of token after being captured
									blue_num_token--;
								}

								// Check if piece moves normally as king: 
								if ((dummyX == dummyX2 - 1) && (dummyY == dummyY2 - 1) && WhitePieces[i].checkKing())
								{
									moveOn = kingMoveNormalWhite1(gameBoard, dummyX, dummyX2, dummyY, dummyY2,
										WhitePieces[i]);
								}

								if ((dummyX == dummyX2 + 1) && (dummyY == dummyY2 - 1) && WhitePieces[i].checkKing())
								{
									moveOn = kingMoveNormalWhite2(gameBoard, dummyX, dummyX2, dummyY, dummyY2,
										WhitePieces[i]);
								}

								// Check if piece attacks as a king: 
								if ((dummyX == dummyX2 - 2) && (dummyY == dummyY2 - 2) && WhitePieces[i].checkKing())
								{
									moveOn = kingAttackWhite1(gameBoard, dummyX, dummyX2, dummyY, dummyY2, WhitePieces[i],
										BluePieces);
									// Decrementing the number of token after being captured
									blue_num_token--;
								}

								if ((dummyX == dummyX2 + 2) && (dummyY == dummyY2 - 2) && WhitePieces[i].checkKing())
								{
									moveOn = kingAttackWhite2(gameBoard, dummyX, dummyX2, dummyY, dummyY2, WhitePieces[i],
										BluePieces);
									// Decrementing the number of token after being captured
									blue_num_token--;
								}
								else
								{
									if (WhitePieces[i].getFillColor() == active)
									{
										deselect = 1;
										if (WhitePieces[i].checkKing())
										{
											WhitePieces[i].setFillColor(sf::Color::Green);
										}

										else
										{
											WhitePieces[i].setFillColor(sf::Color::White);

										}
										break;
									}
								}

								//cout << dummyX2 << " " << dummyY2 << endl;
							}

							//cout << "Ended" << endl;

							// Switch user:
							if (deselect == 0)
							{
								playerTurn = BLUE_PLAYER;
							}
						}
					}
				}
			}
		}
		// Start of Win and lose situation - Results

		if (white_num_token == 0)
		{
			// Also, if the number of token of a specific color is 0, then that color lost
			cout << "BLUE is the winner, White lost!" << endl;
			window.close();
		}
		else if (blue_num_token == 0)
		{
			cout << "WHITE is the winner, Blue lost!" << endl;
			window.close();
		}

		// End of Win and lose situation - End of results

// Draw game board: 
		drawBoard(window, gameBoard, BluePieces, WhitePieces);
	}
}

void drawBoard(sf::RenderWindow& window, Board& gameBoard, Token BluePieces[],
	Token WhitePieces[])
{
	// Redraw window: 
	window.clear();

	// Draw board:
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			window.draw(gameBoard.getTile(i, j));
		}
	}

	// Draw Pieces: 
	for (int i = 0; i < 12; ++i)
	{
		window.draw(BluePieces[i]);
		window.draw(WhitePieces[i]);
	}

	window.display();
}

// Blue Piece Functions:  
bool moveNormal1(Board& gameBoard, int dummyX, int dummyX2, int dummyY,
	int dummyY2, Token& gamePiece)
{
	bool moveOn = false;

	// Space occupied: 
	if (gameBoard.getOccupied(dummyX2, dummyY2))
	{
		cout << "This spot is taken!" << endl;
	}

	// Space not occupied: 
	else
	{
		// Move piece: 
		gamePiece.move(50, 50);
		if (gamePiece.checkKing())
		{
			gamePiece.setFillColor(sf::Color::Cyan);
		}

		else
		{
			gamePiece.setFillColor(sf::Color::Blue);

		}

		// Reallocate piece location: 
		gamePiece.setYLocation(gamePiece.getYLocation() + 50);
		gamePiece.setXLocation(gamePiece.getXLocation() + 50);

		// Update occupied board positions: 
		gameBoard.setNotOccupied(dummyX, dummyY);
		gameBoard.setColor(dummyX, dummyY, NO_TOKEN);

		gameBoard.setOccupied(dummyX2, dummyY2);
		gameBoard.setColor(dummyX2, dummyY2, BLUE_PLAYER);

		moveOn = true;

		// King: 
		if ((int(gamePiece.getYLocation()) / 50) == 7)
		{
			gamePiece.setKing();
			gamePiece.setFillColor(sf::Color::Cyan);
		}
	}

	return (moveOn);
}

bool moveNormal2(Board& gameBoard, int dummyX, int dummyX2, int dummyY,
	int dummyY2, Token& gamePiece)
{
	bool moveOn = false;

	// Space occupied: 
	if (gameBoard.getOccupied(dummyX2, dummyY2))
	{
		cout << "This spot is taken!" << endl;
	}

	// Space not occupied: 
	else
	{
		// Move piece: 
		gamePiece.move(-50, 50);

		if (gamePiece.checkKing())
		{
			gamePiece.setFillColor(sf::Color::Cyan);
		}

		else
		{
			gamePiece.setFillColor(sf::Color::Blue);

		}

		// Reallocate piece location: 
		gamePiece.setYLocation(gamePiece.getYLocation() + 50);
		gamePiece.setXLocation(gamePiece.getXLocation() - 50);

		// Update occupied board positions: 
		gameBoard.setNotOccupied(dummyX, dummyY);
		gameBoard.setColor(dummyX, dummyY, NO_TOKEN);

		gameBoard.setOccupied(dummyX2, dummyY2);
		gameBoard.setColor(dummyX2, dummyY2, BLUE_PLAYER);

		moveOn = true;

		// King: 
		if ((int(gamePiece.getYLocation()) / 50) == 7)
		{
			gamePiece.setKing();
			gamePiece.setFillColor(sf::Color::Cyan);
		}
	}

	return moveOn;
}

bool attack1(Board& gameBoard, int dummyX, int dummyX2, int dummyY,
	int dummyY2, Token& gamePiece, Token whitePieces[])
{
	bool moveOn = false;

	// Piece is taken: 
	if (gameBoard.getOccupied(dummyX2, dummyY2))
	{
		cout << "This spot is taken!" << endl;
	}

	else if (gameBoard.getColor(dummyX2 - 1, dummyY2 - 1) != WHITE_PLAYER)
	{
		cout << "NO Whites here" << endl;
	}

	// Piece not taken: 
	else
	{
		// Move piece: 
		gamePiece.move(100, 100);

		if (gamePiece.checkKing())
		{
			gamePiece.setFillColor(sf::Color::Cyan);
		}

		else
		{
			gamePiece.setFillColor(sf::Color::Blue);

		}

		// Set new piece location: 
		gamePiece.setYLocation(gamePiece.getYLocation() + 100);
		gamePiece.setXLocation(gamePiece.getXLocation() + 100);

		moveOn = true;

		// Update occupied board logic: 
		gameBoard.setNotOccupied(dummyX, dummyY);
		gameBoard.setColor(dummyX, dummyY, NO_TOKEN);

		gameBoard.setOccupied(dummyX2, dummyY2);
		gameBoard.setColor(dummyX2, dummyY2, BLUE_PLAYER);

		// King: 
		if ((int(gamePiece.getYLocation()) / 50) == 7)
		{
			gamePiece.setKing();
			gamePiece.setFillColor(sf::Color::Cyan);
		}

		for (int enemy = 0; enemy < 12; ++enemy)
		{
			if ((int(whitePieces[enemy].getXLocation()) / 50 == (dummyX2 - 1)) &&
				(int(whitePieces[enemy].getYLocation()) / 50 == (dummyY2 - 1)))
			{
				// Get piece off the board: 
				whitePieces[enemy].move(500, 500);

				whitePieces[enemy].setXLocation(500);
				whitePieces[enemy].setYLocation(500);

				gameBoard.setNotOccupied(dummyX2 - 1, dummyY2 - 1);
				gameBoard.setColor(dummyX2 - 1, dummyY2 - 1, NO_TOKEN);
			}
		}
	}

	return moveOn;
}

bool attack2(Board& gameBoard, int dummyX, int dummyX2, int dummyY,
	int dummyY2, Token& gamePiece, Token WhitePieces[])
{
	bool moveOn = false;

	// Tile occupied: 
	if (gameBoard.getOccupied(dummyX2, dummyY2))
	{
		cout << "This spot is taken!" << endl;
	}

	else if (gameBoard.getColor(dummyX2 + 1, dummyY2 - 1) != WHITE_PLAYER)
	{
		cout << "NO Whites here" << endl;
	}

	// Tile not occupied: 
	else
	{
		// Move piece: 
		gamePiece.move(-100, 100);

		if (gamePiece.checkKing())
		{
			gamePiece.setFillColor(sf::Color::Cyan);
		}

		else
		{
			gamePiece.setFillColor(sf::Color::Blue);

		}

		// Set new piece location: 
		gamePiece.setYLocation(gamePiece.getYLocation() + 100);
		gamePiece.setXLocation(gamePiece.getXLocation() - 100);

		moveOn = true;

		// Update tile occupied status: 
		gameBoard.setNotOccupied(dummyX, dummyY);
		gameBoard.setColor(dummyX, dummyY, NO_TOKEN);

		gameBoard.setOccupied(dummyX2, dummyY2);
		gameBoard.setColor(dummyX2, dummyY2, BLUE_PLAYER);

		// King: 
		if ((int(gamePiece.getYLocation()) / 50) == 7)
		{
			gamePiece.setKing();
			gamePiece.setFillColor(sf::Color::Cyan);
		}

		for (int enemy = 0; enemy < 12; ++enemy)
		{
			if ((int(WhitePieces[enemy].getXLocation()) / 50 == (dummyX2 + 1)) &&
				(int(WhitePieces[enemy].getYLocation()) / 50 == (dummyY2 - 1)))
			{
				// Get piece off the board: 
				WhitePieces[enemy].move(500, 500);

				WhitePieces[enemy].setXLocation(500);
				WhitePieces[enemy].setYLocation(500);

				gameBoard.setNotOccupied(dummyX2 + 1, dummyY2 - 1);
				gameBoard.setColor(dummyX2 + 1, dummyY2 - 1, NO_TOKEN);
			}
		}
	}

	return moveOn;
}

bool kingMoveNormal1(Board& gameBoard, int dummyX, int dummyX2, int dummyY,
	int dummyY2, Token& gamePiece)
{
	bool moveOn = false;

	// If tile is occupied: 
	if (gameBoard.getOccupied(dummyX2, dummyY2))
	{
		cout << "This spot is taken!" << endl;
	}

	// Tile not occupied: 
	else
	{
		// Move piece: 
		gamePiece.move(-50, -50);

		if (gamePiece.checkKing())
		{
			gamePiece.setFillColor(sf::Color::Cyan);
		}
		else
		{
			gamePiece.setFillColor(sf::Color::White);
		}

		// Set new tile location: 
		gamePiece.setYLocation(gamePiece.getYLocation() - 50);
		gamePiece.setXLocation(gamePiece.getXLocation() - 50);

		// Update board occupied status: 
		gameBoard.setNotOccupied(dummyX, dummyY);
		gameBoard.setColor(dummyX, dummyY, NO_TOKEN);

		gameBoard.setOccupied(dummyX2, dummyY2);
		gameBoard.setColor(dummyX2, dummyY2, BLUE_PLAYER);

		moveOn = true;
	}

	return moveOn;
}

bool kingMoveNormal2(Board& gameBoard, int dummyX, int dummyX2, int dummyY,
	int dummyY2, Token& gamePiece)
{
	bool moveOn = false;

	// If tile is occupied: 
	if (gameBoard.getOccupied(dummyX2, dummyY2))
	{
		cout << "This spot is taken!" << endl;
	}

	// Tile not occupied: 
	else
	{
		// Move piece: 
		gamePiece.move(+50, -50);

		if (gamePiece.checkKing())
		{
			gamePiece.setFillColor(sf::Color::Cyan);
		}
		else
		{
			gamePiece.setFillColor(sf::Color::White);
		}

		// Set new tile location: 
		gamePiece.setYLocation(gamePiece.getYLocation() - 50);
		gamePiece.setXLocation(gamePiece.getXLocation() + 50);

		// Update board occupied status: 
		gameBoard.setNotOccupied(dummyX, dummyY);
		gameBoard.setColor(dummyX, dummyY, NO_TOKEN);

		gameBoard.setOccupied(dummyX2, dummyY2);
		gameBoard.setColor(dummyX2, dummyY2, BLUE_PLAYER);

		moveOn = true;
	}

	return moveOn;
}

bool kingAttack1(Board& gameBoard, int dummyX, int dummyX2, int dummyY,
	int dummyY2, Token& gamePiece, Token WhitePieces[])
{
	bool moveOn = false;

	// Tile occupied: 
	if (gameBoard.getOccupied(dummyX2, dummyY2))
	{
		cout << "This spot is taken!" << endl;
	}

	else if (gameBoard.getColor(dummyX2 + 1, dummyY2 + 1) != WHITE_PLAYER)
	{
		cout << "No blues here" << endl;
	}

	// Tile not occupied: 
	else
	{
		// Move piece: 
		gamePiece.move(-100, -100);

		if (gamePiece.checkKing())
		{
			gamePiece.setFillColor(sf::Color::Green);
		}
		else
		{
			gamePiece.setFillColor(sf::Color::White);
		}

		// Set new piece location: 
		gamePiece.setYLocation(gamePiece.getYLocation() - 100);
		gamePiece.setXLocation(gamePiece.getXLocation() - 100);

		moveOn = true;

		// Update board occupied status: 
		gameBoard.setNotOccupied(dummyX, dummyY);
		gameBoard.setColor(dummyX, dummyY, NO_TOKEN);

		gameBoard.setOccupied(dummyX2, dummyY2);
		gameBoard.setColor(dummyX2, dummyY2, BLUE_PLAYER);

		for (int enemy = 0; enemy < 12; ++enemy)
		{
			if ((int(WhitePieces[enemy].getXLocation()) / 50 == (dummyX2 + 1)) &&
				(int(WhitePieces[enemy].getYLocation()) / 50 == (dummyY2 + 1)))
			{
				// Get piece off the board: 
				WhitePieces[enemy].move(500, 500);

				WhitePieces[enemy].setXLocation(500);
				WhitePieces[enemy].setYLocation(500);

				gameBoard.setNotOccupied(dummyX2 + 1, dummyY2 + 1);
				gameBoard.setColor(dummyX2 + 1, dummyY2 + 1, NO_TOKEN);
			}
		}
	}

	return moveOn;
}

bool kingAttack2(Board& gameBoard, int dummyX, int dummyX2, int dummyY,
	int dummyY2, Token& gamePiece, Token WhitePieces[])
{
	bool moveOn = false;

	if (gameBoard.getOccupied(dummyX2, dummyY2))
	{
		cout << "This spot is taken!" << endl;
	}

	else if (gameBoard.getColor(dummyX2 - 1, dummyY2 + 1) != WHITE_PLAYER)
	{
		cout << "NO blues here" << endl;
	}

	else
	{
		// Move piece: 
		gamePiece.move(+100, -100);

		if (gamePiece.checkKing())
		{
			gamePiece.setFillColor(sf::Color::Green);
		}
		else
		{
			gamePiece.setFillColor(sf::Color::White);
		}

		// Update piece location: 
		gamePiece.setYLocation(gamePiece.getYLocation() - 100);
		gamePiece.setXLocation(gamePiece.getXLocation() + 100);

		moveOn = true;

		// Update board occupied status: 
		gameBoard.setNotOccupied(dummyX, dummyY);
		gameBoard.setColor(dummyX, dummyY, NO_TOKEN);

		gameBoard.setOccupied(dummyX2, dummyY2);
		gameBoard.setColor(dummyX2, dummyY2, BLUE_PLAYER);

		for (int enemy = 0; enemy < 12; ++enemy)
		{
			if ((int(WhitePieces[enemy].getXLocation()) / 50 == (dummyX2 - 1)) &&
				(int(WhitePieces[enemy].getYLocation()) / 50 == (dummyY2 + 1)))
			{
				// Get piece off the board: 
				WhitePieces[enemy].move(500, 500);

				WhitePieces[enemy].setXLocation(500);
				WhitePieces[enemy].setYLocation(500);

				gameBoard.setNotOccupied(dummyX2 - 1, dummyY2 + 1);
				gameBoard.setColor(dummyX2 - 1, dummyY2 + 1, NO_TOKEN);
			}
		}
	}

	return moveOn;
}

// White Piece Functions: 
bool moveNormalWhite1(Board& gameBoard, int dummyX, int dummyX2, int dummyY,
	int dummyY2, Token& gamePiece)
{
	bool moveOn = false;

	// If tile is occupied: 
	if (gameBoard.getOccupied(dummyX2, dummyY2))
	{
		cout << "This spot is taken!" << endl;
	}

	// Tile not occupied: 
	else
	{
		// Move piece: 
		gamePiece.move(-50, -50);

		if (gamePiece.checkKing())
		{
			gamePiece.setFillColor(sf::Color::Green);
		}
		else
		{
			gamePiece.setFillColor(sf::Color::White);
		}

		// Set new tile location: 
		gamePiece.setYLocation(gamePiece.getYLocation() - 50);
		gamePiece.setXLocation(gamePiece.getXLocation() - 50);

		// Update board occupied status: 
		gameBoard.setNotOccupied(dummyX, dummyY);
		gameBoard.setColor(dummyX, dummyY, NO_TOKEN);

		gameBoard.setOccupied(dummyX2, dummyY2);
		gameBoard.setColor(dummyX2, dummyY2, WHITE_PLAYER);

		moveOn = true;

		// King: 
		if ((int(gamePiece.getYLocation()) / 50) == 0)
		{
			gamePiece.setKing();
			gamePiece.setFillColor(sf::Color::Green);
		}
	}

	return moveOn;
}

bool moveNormalWhite2(Board& gameBoard, int dummyX, int dummyX2, int dummyY,
	int dummyY2, Token& gamePiece)
{
	bool moveOn = false;

	// If tile is occupied: 
	if (gameBoard.getOccupied(dummyX2, dummyY2))
	{
		cout << "This spot is taken!" << endl;
	}

	// Tile not occupied: 
	else
	{
		// Move piece: 
		gamePiece.move(+50, -50);

		if (gamePiece.checkKing())
		{
			gamePiece.setFillColor(sf::Color::Green);
		}
		else
		{
			gamePiece.setFillColor(sf::Color::White);
		}

		// Set new tile location: 
		gamePiece.setYLocation(gamePiece.getYLocation() - 50);
		gamePiece.setXLocation(gamePiece.getXLocation() + 50);

		// Update board occupied status: 
		gameBoard.setNotOccupied(dummyX, dummyY);
		gameBoard.setColor(dummyX, dummyY, NO_TOKEN);

		gameBoard.setOccupied(dummyX2, dummyY2);
		gameBoard.setColor(dummyX2, dummyY2, WHITE_PLAYER);

		moveOn = true;

		// King: 
		if ((int(gamePiece.getYLocation()) / 50) == 0)
		{
			gamePiece.setKing();
			gamePiece.setFillColor(sf::Color::Green);
		}
	}

	return moveOn;
}

bool attackWhite1(Board& gameBoard, int dummyX, int dummyX2, int dummyY,
	int dummyY2, Token& gamePiece, Token BluePieces[])
{
	bool moveOn = false;

	// Tile occupied: 
	if (gameBoard.getOccupied(dummyX2, dummyY2))
	{
		cout << "This spot is taken!" << endl;
	}

	else if (gameBoard.getColor(dummyX2 + 1, dummyY2 + 1) != BLUE_PLAYER)
	{
		cout << "No blues here" << endl;
	}

	// Tile not occupied: 
	else
	{
		// Move piece: 
		gamePiece.move(-100, -100);

		if (gamePiece.checkKing())
		{
			gamePiece.setFillColor(sf::Color::Green);
		}
		else
		{
			gamePiece.setFillColor(sf::Color::White);
		}

		// Set new piece location: 
		gamePiece.setYLocation(gamePiece.getYLocation() - 100);
		gamePiece.setXLocation(gamePiece.getXLocation() - 100);

		moveOn = true;

		// Update board occupied status: 
		gameBoard.setNotOccupied(dummyX, dummyY);
		gameBoard.setColor(dummyX, dummyY, NO_TOKEN);

		gameBoard.setOccupied(dummyX2, dummyY2);
		gameBoard.setColor(dummyX2, dummyY2, WHITE_PLAYER);

		// King: 
		if ((int(gamePiece.getYLocation()) / 50) == 0)
		{
			gamePiece.setKing();
			gamePiece.setFillColor(sf::Color::Green);
		}

		for (int enemy = 0; enemy < 12; ++enemy)
		{
			if ((int(BluePieces[enemy].getXLocation()) / 50 == (dummyX2 + 1)) &&
				(int(BluePieces[enemy].getYLocation()) / 50 == (dummyY2 + 1)))
			{
				// Get piece off the board: 
				BluePieces[enemy].move(500, 500);

				BluePieces[enemy].setXLocation(500);
				BluePieces[enemy].setYLocation(500);

				gameBoard.setNotOccupied(dummyX2 + 1, dummyY2 + 1);
				gameBoard.setColor(dummyX2 + 1, dummyY2 + 1, NO_TOKEN);
			}
		}
	}

	return moveOn;
}

bool attackWhite2(Board& gameBoard, int dummyX, int dummyX2, int dummyY,
	int dummyY2, Token& gamePiece, Token BluePieces[])
{
	bool moveOn = false;

	if (gameBoard.getOccupied(dummyX2, dummyY2))
	{
		cout << "This spot is taken!" << endl;
	}

	else if (gameBoard.getColor(dummyX2 - 1, dummyY2 + 1) != BLUE_PLAYER)
	{
		cout << "NO blues here" << endl;
	}

	else
	{
		// Move piece: 
		gamePiece.move(+100, -100);

		if (gamePiece.checkKing())
		{
			gamePiece.setFillColor(sf::Color::Green);
		}
		else
		{
			gamePiece.setFillColor(sf::Color::White);
		}

		// Update piece location: 
		gamePiece.setYLocation(gamePiece.getYLocation() - 100);
		gamePiece.setXLocation(gamePiece.getXLocation() + 100);

		moveOn = true;

		// Update board occupied status: 
		gameBoard.setNotOccupied(dummyX, dummyY);
		gameBoard.setColor(dummyX, dummyY, NO_TOKEN);

		gameBoard.setOccupied(dummyX2, dummyY2);
		gameBoard.setColor(dummyX2, dummyY2, WHITE_PLAYER);

		// King: 
		if ((int(gamePiece.getYLocation()) / 50) == 0)
		{
			gamePiece.setKing();
			gamePiece.setFillColor(sf::Color::Green);
		}

		for (int enemy = 0; enemy < 12; ++enemy)
		{
			if ((int(BluePieces[enemy].getXLocation()) / 50 == (dummyX2 - 1)) &&
				(int(BluePieces[enemy].getYLocation()) / 50 == (dummyY2 + 1)))
			{
				// Get piece off the board: 
				BluePieces[enemy].move(500, 500);

				BluePieces[enemy].setXLocation(500);
				BluePieces[enemy].setYLocation(500);

				gameBoard.setNotOccupied(dummyX2 - 1, dummyY2 + 1);
				gameBoard.setColor(dummyX2 - 1, dummyY2 + 1, NO_TOKEN);
			}
		}
	}

	return moveOn;
}

bool kingMoveNormalWhite1(Board& gameBoard, int dummyX, int dummyX2, int dummyY,
	int dummyY2, Token& gamePiece)
{
	bool moveOn = false;

	// Space occupied: 
	if (gameBoard.getOccupied(dummyX2, dummyY2))
	{
		cout << "This spot is taken!" << endl;
	}

	// Space not occupied: 
	else
	{
		// Move piece: 
		gamePiece.move(50, 50);
		gamePiece.setFillColor(sf::Color::Green);

		// Reallocate piece location: 
		gamePiece.setYLocation(gamePiece.getYLocation() + 50);
		gamePiece.setXLocation(gamePiece.getXLocation() + 50);

		// Update occupied board positions: 
		gameBoard.setNotOccupied(dummyX, dummyY);
		gameBoard.setColor(dummyX, dummyY, NO_TOKEN);

		gameBoard.setOccupied(dummyX2, dummyY2);
		gameBoard.setColor(dummyX2, dummyY2, WHITE_PLAYER);

		moveOn = true;
	}

	return moveOn;
}

bool kingMoveNormalWhite2(Board& gameBoard, int dummyX, int dummyX2, int dummyY,
	int dummyY2, Token& gamePiece)
{
	bool moveOn = false;

	if (gameBoard.getOccupied(dummyX2, dummyY2))
	{
		cout << "This spot is taken!" << endl;
	}

	// Space not occupied: 
	else
	{
		// Move piece: 
		gamePiece.move(-50, 50);
		gamePiece.setFillColor(sf::Color::Green);

		// Reallocate piece location: 
		gamePiece.setYLocation(gamePiece.getYLocation() + 50);
		gamePiece.setXLocation(gamePiece.getXLocation() - 50);

		// Update occupied board positions: 
		gameBoard.setNotOccupied(dummyX, dummyY);
		gameBoard.setColor(dummyX, dummyY, NO_TOKEN);

		gameBoard.setOccupied(dummyX2, dummyY2);
		gameBoard.setColor(dummyX2, dummyY2, WHITE_PLAYER);

		moveOn = true;
	}

	return moveOn;
}

bool kingAttackWhite1(Board& gameBoard, int dummyX, int dummyX2, int dummyY,
	int dummyY2, Token& gamePiece, Token BluePieces[])
{
	bool moveOn = false;

	// Piece is taken: 
	if (gameBoard.getOccupied(dummyX2, dummyY2))
	{
		cout << "This spot is taken!" << endl;
	}

	else if (gameBoard.getColor(dummyX2 - 1, dummyY2 - 1) != BLUE_PLAYER)
	{
		cout << "NO Whites here" << endl;
	}

	// Piece not taken: 
	else
	{
		// Move piece: 
		gamePiece.move(100, 100);
		gamePiece.setFillColor(sf::Color::Green);

		// Set new piece location: 
		gamePiece.setYLocation(gamePiece.getYLocation() + 100);
		gamePiece.setXLocation(gamePiece.getXLocation() + 100);

		moveOn = true;

		// Update occupied board logic: 
		gameBoard.setNotOccupied(dummyX, dummyY);
		gameBoard.setColor(dummyX, dummyY, NO_TOKEN);

		gameBoard.setOccupied(dummyX2, dummyY2);
		gameBoard.setColor(dummyX2, dummyY2, WHITE_PLAYER);

		for (int enemy = 0; enemy < 12; ++enemy)
		{
			if ((int(BluePieces[enemy].getXLocation()) / 50 == (dummyX2 - 1)) &&
				(int(BluePieces[enemy].getYLocation()) / 50 == (dummyY2 - 1)))
			{
				// Get piece off the board: 
				BluePieces[enemy].move(500, 500);

				BluePieces[enemy].setXLocation(500);
				BluePieces[enemy].setYLocation(500);

				gameBoard.setNotOccupied(dummyX2 - 1, dummyY2 - 1);
				gameBoard.setColor(dummyX2 - 1, dummyY2 - 1, NO_TOKEN);
			}
		}
	}

	return moveOn;
}

bool kingAttackWhite2(Board& gameBoard, int dummyX, int dummyX2, int dummyY,
	int dummyY2, Token& gamePiece, Token BluePieces[])
{
	bool moveOn = false;

	// Tile occupied: 
	if (gameBoard.getOccupied(dummyX2, dummyY2))
	{
		cout << "This spot is taken!" << endl;
	}

	else if (gameBoard.getColor(dummyX2 + 1, dummyY2 - 1) != BLUE_PLAYER)
	{
		cout << "NO Whites here" << endl;
	}

	// Tile not occupied: 
	else
	{
		// Move piece: 
		gamePiece.move(-100, 100);
		gamePiece.setFillColor(sf::Color::Green);


		// Set new piece location: 
		gamePiece.setYLocation(gamePiece.getYLocation() + 100);
		gamePiece.setXLocation(gamePiece.getXLocation() - 100);

		moveOn = true;

		// Update tile occupied status: 
		gameBoard.setNotOccupied(dummyX, dummyY);
		gameBoard.setColor(dummyX, dummyY, NO_TOKEN);

		gameBoard.setOccupied(dummyX2, dummyY2);
		gameBoard.setColor(dummyX2, dummyY2, WHITE_PLAYER);

		for (int enemy = 0; enemy < 12; ++enemy)
		{
			if ((int(BluePieces[enemy].getXLocation()) / 50 == (dummyX2 + 1)) &&
				(int(BluePieces[enemy].getYLocation()) / 50 == (dummyY2 - 1)))
			{
				// Get piece off the board: 
				BluePieces[enemy].move(500, 500);

				BluePieces[enemy].setXLocation(500);
				BluePieces[enemy].setYLocation(500);

				gameBoard.setNotOccupied(dummyX2 + 1, dummyY2 - 1);
				gameBoard.setColor(dummyX2 + 1, dummyY2 - 1, NO_TOKEN);
			}
		}
	}

	return moveOn;
}