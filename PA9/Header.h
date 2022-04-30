#ifndef Header
#include"Classes.h"
#include "Test.h"

void game_loop();
void drawBoard(sf::RenderWindow& window, Board& gameBoard, Token BluePieces[],	Token WhitePieces[]);
bool moveNormal1(Board& gameBoard, int dummyX, int dummyX2, int dummyY,	int dummyY2, Token& gamePiece);
bool moveNormal2(Board& gameBoard, int dummyX, int dummyX2, int dummyY, int dummyY2, Token& gamePiece);
bool attack1(Board& gameBoard, int dummyX, int dummyX2, int dummyY,	int dummyY2, Token& gamePiece, Token whitePieces[]);
bool attack2(Board& gameBoard, int dummyX, int dummyX2, int dummyY, int dummyY2, Token& gamePiece, Token WhitePieces[]);
bool kingMoveNormal1(Board& gameBoard, int dummyX, int dummyX2, int dummyY,	int dummyY2, Token& gamePiece);
bool kingMoveNormal2(Board& gameBoard, int dummyX, int dummyX2, int dummyY, int dummyY2, Token& gamePiece);
bool kingAttack1(Board& gameBoard, int dummyX, int dummyX2, int dummyY,	int dummyY2, Token& gamePiece, Token WhitePieces[]);
bool kingAttack2(Board& gameBoard, int dummyX, int dummyX2, int dummyY,	int dummyY2, Token& gamePiece, Token WhitePieces[]);
bool moveNormalWhite1(Board& gameBoard, int dummyX, int dummyX2, int dummyY,	int dummyY2, Token& gamePiece);
bool moveNormalWhite2(Board& gameBoard, int dummyX, int dummyX2, int dummyY,	int dummyY2, Token& gamePiece);
bool attackWhite1(Board& gameBoard, int dummyX, int dummyX2, int dummyY, 	int dummyY2, Token& gamePiece, Token BluePieces[]);
bool attackWhite2(Board& gameBoard, int dummyX, int dummyX2, int dummyY,
	int dummyY2, Token& gamePiece, Token BluePieces[]);
bool kingMoveNormalWhite1(Board& gameBoard, int dummyX, int dummyX2, int dummyY,	int dummyY2, Token& gamePiece);
bool kingMoveNormalWhite2(Board& gameBoard, int dummyX, int dummyX2, int dummyY,	int dummyY2, Token& gamePiece);
bool kingAttackWhite1(Board& gameBoard, int dummyX, int dummyX2, int dummyY,	int dummyY2, Token& gamePiece, Token BluePieces[]);
bool kingAttackWhite2(Board& gameBoard, int dummyX, int dummyX2, int dummyY,	int dummyY2, Token& gamePiece, Token BluePieces[]);
#endif // !Header

