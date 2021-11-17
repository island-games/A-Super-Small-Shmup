#include "player.h"
#include "playerBullets.h"
#include "objectHolder.h"

player::player()
{
	isDead = false;
	x = 344;
	y = 505;
	width = 32;
	height = 32;
	lives = 10;
	activeBullets = 0;
	health = 1;
	respawnWaitTime = 0;
	invincibleTime = 0;
	hasPowerUp = false;
}

void player::Respawn()
{
	if(respawnWaitTime > 60)
	{
		health = 1;
		activeBullets = 0;
		x = 344;
		y = 505;
		respawnWaitTime = 0;
		invincibleTime = 90;
		hasPowerUp = false;
	}
	
}

void player::CheckDeath()
{
	if(health <= 0)
	{
		PlaySound(playerDeathSnd);
		listOfExplosionObj.push_back(new explosion(x - 8,y - 8,0));
		lives -= 1;
		
		if(lives <= 0)
		{
			gameState = "gameOver";
			isDead = true;
			ClearGame();
			if(gameManagerObj->hasFiredShot == false)
			{
				Bartender_UnlockTrophy(10);
			}
		}
	}
}

void player::Shoot()
{
	if(controllerObj->isCrossPressed == true && controllerObj->canCrossBePressed == true)
	{
		if(hasPowerUp == false)
		{
			if(listOfPlayerBulletsObj.size() < 2)
			{
				listOfPlayerBulletsObj.push_back(new playerBullets(x + 14, y - 5));
				PlaySound(playerShotSnd);
				gameManagerObj->hasFiredShot = true;
			}
		}
		
		if(hasPowerUp == true)
		{
			if(listOfPlayerBulletsObj.size() < 4)
			{
				listOfPlayerBulletsObj.push_back(new playerBullets(x + 8, y - 5));
				listOfPlayerBulletsObj.push_back(new playerBullets(x + 24, y - 5));
				PlaySound(playerShotSnd);
				gameManagerObj->hasFiredShot = true;
			}
		}
	}
}


void player::GameOver()
{
	
}

void player::CheckCollision()
{
	for(int i = 0; i < listOfPowerUpObj.size(); i++)
	{
		if(x + width >= listOfPowerUpObj[i]->x && x <= listOfPowerUpObj[i]->x +listOfPowerUpObj[i]->width)
		{
			if(y + height >= listOfPowerUpObj[i]->y && y <= listOfPowerUpObj[i]->y + listOfPowerUpObj[i]->height)
			{
				listOfPowerUpObj[i]->isDead = true;
				hasPowerUp = true;
				PlaySound(bonusSnd);
			}
		}
	}
	
	
	if(invincibleTime <= 0)
	{
		for(int i = 0; i < listOfEnemyObj.size(); i++)
		{
			if(x + width >= listOfEnemyObj[i]->x && x <= listOfEnemyObj[i]->x +listOfEnemyObj[i]->width)
			{
				if(y + height >= listOfEnemyObj[i]->y && y <= listOfEnemyObj[i]->y + listOfEnemyObj[i]->height)
				{
					health = 0;
					listOfEnemyObj[i]->health = 0;
				}
			}
		}
		
		for(int i = 0; i < listOfEnemyBulletsObj.size(); i++)
		{
			if(x + width >= listOfEnemyBulletsObj[i]->x && x <= listOfEnemyBulletsObj[i]->x +listOfEnemyBulletsObj[i]->width)
			{
				if(y + height >= listOfEnemyBulletsObj[i]->y && y <= listOfEnemyBulletsObj[i]->y + listOfEnemyBulletsObj[i]->height)
				{
					health = 0;
					listOfEnemyBulletsObj[i]->isDead = true;
				}
			}
		}
	}
	else
	{
		invincibleTime--;
	}
}

void player::Move()
{
	if(controllerObj->isLeftPressed == true || controllerObj->leftStickX < 60)
	{
		x -= 5;
		if(x < 10)
		{
			x = 10;
		}
	}
	
	if(controllerObj->isRightPressed == true || controllerObj->leftStickX > 198)
	{
		x += 5;
		
		if(x + width > 710)
		{
			x = 710-width;
		}
	}
}

void player::PauseGame()
{
	if(controllerObj->isStartPressed == true && controllerObj->canStartBePressed == true)
	{
		isPaused = true;
		listOfPauseObj.push_back(new pause());
		controllerObj->GetCanPresses();
	}
}

void player::Draw()
{
	int opactiy = 255;
	int green = 255;
	int blue = 255;
	
	if(invincibleTime > 0)
	{
		opactiy = 125;
	}
	
	if(hasPowerUp == true)
	{
		green = 125;
		blue = 125;
	}
	
	if(health > 0)
	{
		vita2d_draw_texture_tint_part(spriteTexture, x, y, 0, 0, 32, 32, RGBA8(255,green,blue,opactiy));
	}
	
}

bool player::Update()
{
	if(health > 0)
	{
		Move();
		CheckCollision();
		Shoot();
		PauseGame();
		CheckDeath();
	}
	else
	{
		if(lives > 0)
		{
			respawnWaitTime++;
			Respawn();
		}
	}
	
	return isDead;
}