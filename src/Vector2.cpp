#include "Vector2.h"

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(int tempValue)
{
	int x = tempValue;
	int y = tempValue;
}

Vector2::Vector2(int tempX, int tempY)
{
	x = tempX;
	y = tempY;
}

void Vector2::setX(int temp)
{
	x =  temp;
}

void Vector2::setY(int temp)
{
	y = temp;
}

int Vector2::getX()
{
	return x;
}

int Vector2::getY()
{
	return y;
}