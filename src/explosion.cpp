#include "objectHolder.h"
#include "explosion.h"

	explosion::explosion(int tempX, int tempY, int tempExplosionType)
	{
		x = tempX;
		y = tempY;
		explosionType = tempExplosionType;
		explosionTime =0;
		isDead = false;
	}
	
void explosion::Draw()
{
	if(explosionType == 0)
	{
		if(explosionTime <= 4)
		{
			vita2d_draw_texture_part(playerExplosionTexture, x, y, 2, 2, 48,48);
		}
		else if(explosionTime >= 5 && explosionTime <=8)
		{
			vita2d_draw_texture_part(playerExplosionTexture, x, y, 52, 2, 48,48);
		}
		else if(explosionTime >= 9 && explosionTime <=12)
		{
			vita2d_draw_texture_part(playerExplosionTexture, x, y, 102, 2, 48,48);
		}
		else if(explosionTime >= 13 && explosionTime <=16)
		{
			vita2d_draw_texture_part(playerExplosionTexture, x, y, 2, 52, 48,48);
		}
		else if(explosionTime >= 17 && explosionTime <=20)
		{
			vita2d_draw_texture_part(playerExplosionTexture, x, y, 52, 52, 48,48);
		}
		else if(explosionTime >= 21 && explosionTime <=24)
		{
			vita2d_draw_texture_part(playerExplosionTexture, x, y, 102, 52, 48,48);
		}
		else if(explosionTime >= 25 && explosionTime <=28)
		{
			vita2d_draw_texture_part(playerExplosionTexture, x, y, 2, 102, 48,48);
		}
	}
	
	if(explosionType == 1)
	{
		if(explosionTime <= 4)
		{
			vita2d_draw_texture_part(enemyExplosionTexture, x, y, 2, 2, 64,64);
		}
		else if(explosionTime >= 5 && explosionTime <=8)
		{
			vita2d_draw_texture_part(enemyExplosionTexture, x, y, 68, 2, 64,64);
		}
		else if(explosionTime >= 9 && explosionTime <=12)
		{
			vita2d_draw_texture_part(enemyExplosionTexture, x, y, 134, 2, 64,64);
		}
		else if(explosionTime >= 13 && explosionTime <=16)
		{
			vita2d_draw_texture_part(enemyExplosionTexture, x, y, 2, 68, 64,64);
		}
		else if(explosionTime >= 17 && explosionTime <=20)
		{
			vita2d_draw_texture_part(enemyExplosionTexture, x, y, 68, 68, 64,64);
		}

	}
}

bool explosion::Update()
{
	explosionTime++;
	if(explosionTime > 30)
	{
		isDead = true;
	}
	
	return isDead;
}