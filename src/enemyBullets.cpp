#include "enemyBullets.h"
#include "objectHolder.h"
enemyBullets::enemyBullets(int xPos, int yPos)
{
	x = xPos;
	y = yPos;
	moveSpeed = 6;
	xSpeed = 0;
	height = 12;
	width = 4;
	isDead = false;
}

enemyBullets::enemyBullets(int xPos, int yPos, int xSpeedTemp, int ySpeedTemp)
{
	x = xPos;
	y = yPos;
	moveSpeed = ySpeedTemp;
	xSpeed = xSpeedTemp;
	height = 8;
	width = 8;
	isDead = false;
}

void enemyBullets::Draw()
{
	//vita2d_draw_rectangle(x, y, width, height, RGBA8(255,128,0,255));
	vita2d_draw_texture_tint(bulletTexture, x, y, RGBA8(255,128,0,255));
}

void enemyBullets::Move()
{
	y += moveSpeed;
	x += xSpeed;
	
	if(y > 544)
	{
		isDead = true;
	}
}

bool enemyBullets::Update()
{
	Move();
	
	return isDead;
}