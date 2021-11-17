#include "objectHolder.h"
#include "powerUp.h"

powerUp::powerUp(int tempX, int tempY)
{
	x = tempX;
	y = tempY;
	width = 16;
	height = 16;
	
	isDead = false;
}

void powerUp::Draw()
{
	vita2d_draw_texture_part(ufoTexture, x, y, 36, 2, 16, 16);
}

bool powerUp::Update()
{
	y+= 3;
	
	if(y > 560)
	{
		isDead = true;
	}
		
	
	return isDead;
}