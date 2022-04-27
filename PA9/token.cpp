#include "Header.h"


void Token::setNewFillColor(sf::Color newColor)
{
	this->setFillColor(newColor);
}

double Token::getXLocation(void)
{
	return this->mXPos;
}

double Token::getYLocation(void)
{
	return this->mYPos;
}

void Token::setXLocation(double newXLocation)
{
	this->mXPos = newXLocation;
}
void Token::setYLocation(double newYLocation)
{
	this->mYPos = newYLocation;
}

void Token::setKing(void)
{
	this->mKing = true; 	
}

bool Token::checkKing(void)
{
	return this->mKing; 
}
