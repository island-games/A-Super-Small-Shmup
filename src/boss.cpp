#include "boss.h"
#include "objectHolder.h"

boss::boss()
{
	y = 32;
	x = -100;
	health = 50;
	dieTime = 0;
	selectedAttackPattern = -1;
	attackTime = 0;
	attackTimeLimit = 0;
	animationTime = 0;
	moveSpeed = 3;
	direction = "";
	attackWaitTime = 0;
	waitToMoveTime = 0;
	characterState  = "enter";
	if(bossTexture == NULL)
	 {
		 bossTexture = vita2d_load_PNG_file((char*)"app0:img/boss.png");
	 }
	
	isDead = false;
}

void boss::Draw()
{
	int redTint = 0;
	int blueTint = 0;
	int greenTint = 0;
	if(health > 40)
	{
		redTint = 255;
		blueTint = 255;
		greenTint = 255;
		
	}
	
	else if(health >= 21 && health <= 40)
	{
		redTint = 255;
		blueTint = 235;
		greenTint = 235;
	}
	else if(health >= 11 && health <= 20)
	{
		redTint = 255;
		blueTint = 205;
		greenTint = 205;
	}
	else
	{
		redTint = 255;
		blueTint = 150;
		greenTint = 150;
	}
	animationTime++;
	
	if(characterState == "enter")
	{
		vita2d_draw_texture_tint_part(bossTexture, x, y, 2, 2, 90, 105, RGBA8(redTint,blueTint,greenTint,255));
	}
	
	else if(characterState == "wait")
	{
		if(playerObj !=NULL)
		{
			if(playerObj->x < x - 100)
			{
				vita2d_draw_texture_tint_part(bossTexture, x, y, 2, 109, 90, 105, RGBA8(redTint,blueTint,greenTint,255));
			}
			else if(playerObj->x > x + 90 + 100)
			{
				vita2d_draw_texture_tint_part(bossTexture, x, y, 2, 216, 90, 105, RGBA8(redTint,blueTint,greenTint,255));
			}
			
			else
			{
				vita2d_draw_texture_tint_part(bossTexture, x, y, 2, 2, 90, 105, RGBA8(redTint,blueTint,greenTint,255));
			}
			
		}
		else
		{
			vita2d_draw_texture_tint_part(bossTexture, x, y, 2, 2, 90, 105, RGBA8(redTint,blueTint,greenTint,255));
		}
	}
	
	else if(characterState == "attack")
	{
		if(attackTime < 10)
		{
			vita2d_draw_texture_tint_part(bossTexture, x, y, 2, 323, 90, 105, RGBA8(redTint,blueTint,greenTint,255));
		}
		else
		{
		
			if(animationTime <= 5)
			{
				vita2d_draw_texture_tint_part(bossTexture, x, y, 2, 430, 90, 105, RGBA8(redTint,blueTint,greenTint,255));
			}
			else
			{
				vita2d_draw_texture_tint_part(bossTexture, x, y, 2, 537, 90, 105, RGBA8(redTint,blueTint,greenTint,255));
			}
		}
	}
	
	else if(characterState == "die")
	{
		vita2d_draw_texture_tint_part(bossTexture, x, y, 2, 430, 90, 105, RGBA8(redTint,blueTint,greenTint,255));
	}
	else
	{
		vita2d_draw_texture_tint_part(bossTexture, x, y, 2, 2, 90, 105, RGBA8(redTint,blueTint,greenTint,255));
	}
	
	if(animationTime >= 10)
	{
		animationTime = 0;
	}
}

void boss::DecideAction()
{
	
	if(health > 40)
	{
		moveSpeed = 3;
	}
	
	else if(health >= 21 && health <= 40)
	{
		moveSpeed = 4;
	}
	else if(health >= 11 && health <= 20)
	{
		moveSpeed = 5;
	}
	else
	{
		moveSpeed = 6;
	}
	
	
	
	if(characterState == "enter")
	{
		Enter();
		return;
	}
	
	if(characterState == "wait")
	{
		Wait();
		Move();
		return;
	}
	
	if(characterState == "attack")
	{
		Attack();
		return;
	}
	
	if(characterState == "die")
	{
		Die();
		return;
	}
}

void boss::Move()
{
	if(waitToMoveTime > 0)
	{
		waitToMoveTime--;
		return;
	}
	
	if(direction == "")
	{
		int rndNumber = rand() % 2;
		
		if(rndNumber == 0)
		{
			direction = "left";
		}
		
		else
		{
			direction = "right";
		}
	}
	
	if(direction == "left")
	{
		x-= moveSpeed;
		if(x <= 24)
		{
			x = 24;
			direction = "right";
			return;
		}
	}
	
	if(direction == "right")
	{
		x+= moveSpeed;
		if(x >= 606)
		{
			x = 606;
			direction = "left";
			return;
		}
	}
}

void boss::Wait()
{
	if(waitToMoveTime > 0)
	{
		return;
	}
	
	attackWaitTime--;
	if(attackWaitTime <= 0)
	{
		characterState = "attack";
	}
}

void boss::Shoot(int xSpeed, int ySpeed)
{
	listOfEnemyBulletsObj.push_back(new enemyBullets(x+40,y+105,xSpeed,ySpeed));
	PlaySound(enemyShotSnd);
}

void boss::Attack()
{
	if(selectedAttackPattern == -1)
	{
		attackTime = 0;
		
		selectedAttackPattern = rand() % 5;
		
	}
	
	attackTime++;
	
	switch(selectedAttackPattern)
	{
		case 0:
			attackTimeLimit = 150;
			if(attackTime == 10 || attackTime == 20 || attackTime == 30 || attackTime == 40|| attackTime == 50|| attackTime == 60 || attackTime == 70 || attackTime == 80 || attackTime == 90|| attackTime == 90|| attackTime == 100|| attackTime == 110|| attackTime == 120)
			{
				// Shooting Straight down
				
				
				Shoot(0,6);
			}
			Move();
		break;
		
		
		case 1:
			attackTimeLimit = 270;
			if(attackTime == 30 || attackTime == 60 || attackTime == 90 || attackTime == 120 || attackTime == 150 || attackTime == 180 || attackTime == 210 || attackTime == 240)
			{
				// Shooting 5 in a pattern
				
				Shoot(5,7);
				Shoot(2,7);
				Shoot(0,7);
				Shoot(-2,7);
				Shoot(-5,7);
			}
			
		break;
		
		case 2:
			attackTimeLimit = 150;
			if(attackTime == 10 || attackTime == 20 || attackTime == 30 || attackTime == 40|| attackTime == 50|| attackTime == 60 || attackTime == 70 || attackTime == 80 || attackTime == 90|| attackTime == 90|| attackTime == 100|| attackTime == 110|| attackTime == 120)
			{
				// Bullets shoot in the opposite direction where the boss is moving 
				if(direction == "left")
				{
					Shoot(3,8);
				}
				else
				{
					Shoot(-3,8);
				}
				
			}
			Move();
			
		break;
		
		case 3:
			
			if(x != 315)
				{
					attackTime = 0;
					if(x < 315)
					{
						direction = "right";
						Move();
						
						if(x > 315)
						{
							x = 315;
						}
					}
					
					else if(x > 315)
					{
						direction = "left";
						Move();
						
						if(x < 315)
						{
							x = 315;
						}
					}
				}
				
				attackTimeLimit = 150;
			
			if(attackTime == 10 || attackTime == 20 || attackTime == 30 || attackTime == 40|| attackTime == 50|| attackTime == 60 || attackTime == 70 || attackTime == 80 || attackTime == 90|| attackTime == 90|| attackTime == 100|| attackTime == 110|| attackTime == 120)
			{
				// Move to the center of the screen then spray bullets from left to right and back to the left
				int tempXSpeed = 0;
				
				switch(attackTime)
				{
					case 10:
						tempXSpeed = -6;
					break;
					
					case 20:
						tempXSpeed = -4;
					break;
					
					case 30:
						tempXSpeed = -2;
					break;
					
					case 40:
						tempXSpeed = 0;
					break;
					
					case 50:
						tempXSpeed = 2;
					break;
					
					case 60:
						tempXSpeed = 4;
					break;
					
					case 70:
						tempXSpeed = 6;
					break;
					
					case 90:
						tempXSpeed = 4;
					break;
					
					case 100:
						tempXSpeed = 2;
					break;
					
					case 110:
						tempXSpeed = 0;
					break;
					
					case 120:
						tempXSpeed = -2;
					break;
					

				}

				Shoot(tempXSpeed, 9);
			
			}
			
		break;
		
		case 4:
			
			if(x != 315)
				{
					attackTime = 0;
					if(x < 315)
					{
						direction = "right";
						Move();
						
						if(x > 315)
						{
							x = 315;
						}
					}
					
					else if(x > 315)
					{
						direction = "left";
						Move();
						
						if(x < 315)
						{
							x = 315;
						}
					}
				}
			
			attackTimeLimit = 270;
				
			if(attackTime == 30 || attackTime == 60 || attackTime == 90 || attackTime == 120 || attackTime == 150 || attackTime == 180 || attackTime == 210 || attackTime == 240)
			{
				// Shooting  8 in a pattern from the center of the screen
				Shoot(6,8);
				Shoot(4,8);
				Shoot(2,8);
				Shoot(1,8);
				Shoot(0,8);
				Shoot(-1,8);
				Shoot(-6,8);
				Shoot(-4,8);
				Shoot(-2,8);
			}
			
		break;
					
	}
	
	
	
	if(attackTime >= attackTimeLimit)
	{
		selectedAttackPattern = -1;
		attackTime = 0;
		attackTimeLimit = 0;
		attackWaitTime = rand() % 120 + 240;
		characterState = "wait";
		waitToMoveTime = 90;
	}
}

void boss::Enter()
{
	x += 3;
	if (x >= 315)
	{
		x = 315;
		characterState = "wait";
		attackWaitTime = 120;
	}
}

void boss::Die()
{
	dieTime++;
	if(dieTime >= 120)
	{
		isDead = true;
		gameState = "thanks";
		Bartender_UnlockTrophy(4);
	}
	
	if(dieTime == 1)
	{
		listOfExplosionObj.push_back(new explosion(x - 16, y +32, 0));
		PlaySound(playerDeathSnd);
	}
	
	if(dieTime == 20)
	{
		listOfExplosionObj.push_back(new explosion(x + 60, y + 64, 0));
		PlaySound(playerDeathSnd);
	}
	
	if(dieTime == 40)
	{
		listOfExplosionObj.push_back(new explosion(x + 40, y + 80, 0));
		PlaySound(playerDeathSnd);
	}
	
	if(dieTime == 60)
	{
		listOfExplosionObj.push_back(new explosion(x + 5, y + 10, 0));
		PlaySound(playerDeathSnd);
	}
	
	if(dieTime == 80)
	{
		listOfExplosionObj.push_back(new explosion(x + 30, y + 40, 0));
		PlaySound(playerDeathSnd);
	}
	
	if(dieTime == 100)
	{
		listOfExplosionObj.push_back(new explosion(x -16, y + 72, 0));
		PlaySound(playerDeathSnd);
	}
}

void boss::CheckDeath() 
{
	if(health <= 0 && characterState != "die")
	{
		characterState = "die";
		score += 5000;
		for(int i = 0; i < listOfEnemyObj.size(); i++)
		{
			listOfEnemyObj[i]->health = 0;
		}
	}
}

bool boss::Update()
{
	DecideAction();
	CheckDeath();
	return isDead;
}