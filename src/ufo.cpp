#include "objectHolder.h"
#include "ufo.h"

ufo::ufo(int tempX, int tempY)
{
	x = tempX;
	y = tempY;
	width = 32;
	height = 27;
	isDead = false;
	health = 1;
	direction = "";
	 if(x < 0)
	 {
		 direction = "right";
	 }
	 else
	 {
		 direction= "left";
	 }
	
}

void ufo::Move()
{
	if(direction == "right")
	{
		x += 5;
	}
	
	else
	{
		x -= 5;
	}
	
	if(x < -64)
	{
		isDead = true;
	}
	
	if(x > 780)
	{
		isDead = true;
	}
	
}

void ufo::CheckLife()
{
	if(health <= 0)
	{
		listOfPowerUpObj.push_back(new powerUp(x+8,y+8));
		listOfExplosionObj.push_back(new explosion(x - 16,y - 16,1));
		isDead = true;
		score += 500;
		Bartender_UnlockTrophy(8);
	}
}

void ufo::Draw()
{
	vita2d_draw_texture_part(ufoTexture, x, y, 2, 2, 32, 27);
}

bool ufo::Update()
{
	Move();
	CheckLife();
	
	return isDead;
}