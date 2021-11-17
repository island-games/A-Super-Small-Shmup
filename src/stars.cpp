#include "objectHolder.h"
#include "stars.h"

stars::stars(int tempX, int tempY, int tempTime)
{
	x = tempX;
	y = tempY;
	time = tempTime;
	isDead = false;
}

void stars::Draw()
{
	if(time <= 29)
	{
		vita2d_draw_texture_tint_part(splashScreenTexture, x, y, 0, 0, 1,1, RGBA8(255,80,0,255));
		
	}
	else if(time >= 30 && time <= 59)
	{
		vita2d_draw_texture_tint_part(splashScreenTexture, x, y, 0, 0, 1,1, RGBA8(255,255,255,255));
	}
	else
	{
		vita2d_draw_texture_tint_part(splashScreenTexture, x, y, 0, 0, 1,1, RGBA8(58,120,255,255));

	}
}

bool stars::Update()
{
	y += 3;
	time++;
	if(y > 544)
	{
		y = y-544;
	}
	
	if(time >= 90)
	{
		time = 0;
	}
	
	return isDead;
}