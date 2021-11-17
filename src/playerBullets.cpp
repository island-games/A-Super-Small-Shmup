#include "playerBullets.h"
#include "objectHolder.h"

playerBullets::playerBullets(int xPos, int yPos)
{
	x = xPos;
	y = yPos;
	width = 4;
	height = 12;
	isDead = false;
}

void playerBullets::Draw()
{
	//vita2d_draw_rectangle(x, y, width, height, RGBA8(0,0,255,255));
	vita2d_draw_texture_tint(bulletTexture, x, y, RGBA8(0,0,255,255));
}

void playerBullets::Move()
{
	y -= 8;
	
	if(y < -12)
	{
		isDead = true;
	}
}

void playerBullets::CheckCollision()
{
	for(int i = 0; i < listOfUfoObj.size(); i++)
	{
		if(x + width >= listOfUfoObj[i]->x && x <= listOfUfoObj[i]->x +listOfUfoObj[i]->width)
		{
			if(y + height >= listOfUfoObj[i]->y && y <= listOfUfoObj[i]->y + listOfUfoObj[i]->height)
			{
				isDead = true;
				listOfUfoObj[i]->health -= 1;
				PlaySound(impactSnd);
				return;
			}
		}
	}
	
	for(int i = 0; i < listOfEnemyObj.size(); i++)
	{
		if(x + width >= listOfEnemyObj[i]->x && x <= listOfEnemyObj[i]->x +listOfEnemyObj[i]->width)
		{
			if(y + height >= listOfEnemyObj[i]->y && y <= listOfEnemyObj[i]->y + listOfEnemyObj[i]->height)
			{
				isDead = true;
				listOfEnemyObj[i]->health -= 1;
				PlaySound(impactSnd);
				return;
			}
		}
	}
	
	for(int i = 0; i < listOfBossObj.size(); i++)
	{
		if(x <= listOfBossObj[i]->x + 60 && x + width > listOfBossObj[i]->x + 30)
		{
			if(y <= listOfBossObj[i]->y + 75 && y + height >= listOfBossObj[i]->y + 49)
			{
				isDead = true;
				listOfBossObj[i]->health -= 1;
				PlaySound(impactSnd);
				return;
			}
		}
	}

}

bool playerBullets::Update()
{
	Move();
	CheckCollision();
	return isDead;
}