#include "Header.h"

void TestAll()
{
	TestMove();
	TestKing();
	TestKingMove();
	TestWhiteMove();
}
void TestMove()
{
	Board gameBoard;
	int dummyX = 1, dummyX2 = 2, dummyY2 = 3, dummyY= 3;
	Token gamePiece;
	moveNormal1(gameBoard, dummyX, dummyX2, dummyY, dummyY2, gamePiece);
}
void TestKing()
{
	Board gameBoard;
	int dummyX = 1, dummyX2 = 2, dummyY2 = 3, dummyY = 3;
	Token gamePiece;
	gamePiece.setKing();
}
void TestKingMove()
{
	Board gameBoard;
	int dummyX = 1, dummyX2 = 2, dummyY2 = 3, dummyY = 3;
	Token gamePiece;
	kingMoveNormal1(gameBoard, dummyX, dummyX2, dummyY, dummyY2, gamePiece);

}
void TestWhiteMove()
{
	Board gameBoard;
	int dummyX = 1, dummyX2 = 2, dummyY2 = 3, dummyY = 3;
	Token gamePiece;
	moveNormalWhite1(gameBoard, dummyX, dummyX2, dummyY, dummyY2, gamePiece);
}