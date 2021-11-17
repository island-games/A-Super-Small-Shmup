#include "enemy.h"
#include "objectHolder.h"
#include "math.h"


enemy::enemy(int xPos, int yPos, int tempType, int enemyGridPositionTempx, int enemyGridPositionTempy, std::vector<Vector2> listOfPoints, bool tempShootWhileEntering)
{
	waitTime = 0;
	RAD = 0.0174533f;
	angle = 0;
	isDead = false;
	inPosition = false;
	xDirection = "";
	yDirection = "";
	x = xPos;
	y = yPos;
	enemyGridPositionX = enemyGridPositionTempx;
	enemyGridPositionY = enemyGridPositionTempy;
	width = 32;
	height = 32;
	shootWhileEntering = tempShootWhileEntering;
	enemyType = tempType;
	points = listOfPoints;
	RemovePoint();
	if(enemyType <= 3)
	{
		health = 1;
		
	}
	else if(enemyType>=4)
	{
		health = 2;
	}
	shootTime;
	if(shootWhileEntering == true)
	{
		shootTime.push_back(120);
	}
}

void enemy::RemovePoint()
{
	if(points.size() > 0)
	{
		points.erase(points.begin() + 0);
		
		if(points.size() <= 0)
		{
			return;
		}
		
		if(x < points[0].x)
		{
			xDirection = "right";
		}
		else
		{
			xDirection = "left";
		}
		
		if(y < points[0].y)
		{
			yDirection = "down";
		}
		else
		{
			yDirection = "up";
		}
		
	}
}

void enemy::CheckHealth()
{
	if(health <= 0)
	{
		isDead = true;
		listOfExplosionObj.push_back(new explosion(x - 16-8,y - 16-8,1));
		
		
		switch (enemyType){
			
			case 1:
				score += 5;
			break;
			
			case 2:
				score += 10;
			break;
			
			case 3:
				score += 15;
			break;
			
			case 4:
				score += 25;
			break;
			
			case 5:
				score += 50;
			break;
			
			
		
		}
			
		
	}
}

void enemy::Move()
{
	if(waitTime > 0)
	{
		waitTime--;
		return;
	}
	
	if(points.size() <= 0)
	{
		if(xDirection != "" && yDirection != "")
		{
			int tempX = 90 + (enemyGridPositionX * 52) + totalGridOffsetDestination + columnOffsetDestination[enemyGridPositionX];
			int tempY = 20 + (enemyGridPositionY * 45);
			
			
			
			if(enemyGridPositionX == -1 || enemyGridPositionY == -1)
			{
				points.push_back(gameManagerObj->SetPoint(rand() % 32 + (playerObj->x - 16),650));
				return;
			}
			
			if(x < tempX)
			{
				xDirection = "right";
			}
			if(x > tempX)
			{
				xDirection = "left";
			}
			
			if(xDirection == "left" || xDirection == "l")
			{
				x -= enemyMoveSpeed;
				if(x < tempX)
				{
					x = tempX;
					xDirection = "l";
				}
			}
		
			if(xDirection == "right" || xDirection == "r")
			{ 
				x += enemyMoveSpeed;
				if(x > tempX)
				{
					x = tempX;
					xDirection = "r";
				}
			}
		
			if(yDirection == "up")
			{
				y-= enemyMoveSpeed;
				if(y < tempY)
				{
					y = tempY;
					yDirection = "u";
				}
			}
		
			if(yDirection == "down")
			{
				y+= enemyMoveSpeed;
				if(y > tempY)
				{
					y = tempY;
					yDirection = "d";
				}
			}
			
		
			if(x == tempX && y == tempY)
			{
				yDirection = "";
				xDirection = "";
				inPosition = true;
				if(gameManagerObj != NULL)
				{
					gameManagerObj->canGetBonus = false;
				}
			}
			
			return;
		}
		else
		{
			if(x < 90 + (enemyGridPositionX * 52) + totalGridOffsetDestination + columnOffsetDestination[enemyGridPositionX])
			{
				x++;
			}
			
			if( x > 90 + (enemyGridPositionX * 52) + totalGridOffsetDestination + columnOffsetDestination[enemyGridPositionX])
			{
				x--;
			}
			
			
			
			y = 20 + (enemyGridPositionY * 45);
		}
		
		if(direction == "left")
		{
			x -= enemyMoveSpeed;
		}
		
		if(direction == "right")
		{
			x += enemyMoveSpeed;
		}
	}
	else
	{
		if(xDirection == "left")
		{
			x -= enemyMoveSpeed;
			if(x < points[0].x)
			{
				x = points[0].x;
				xDirection = "l";
			}
		}
		
		if(xDirection == "right")
		{
			x += enemyMoveSpeed;
			if(x > points[0].x)
			{
				x = points[0].x;
				xDirection = "r";
			}
		}
		
		if(yDirection == "up")
		{
			y-= enemyMoveSpeed;
			if(y < points[0].y)
			{
				y = points[0].y;
				yDirection = "u";
			}
		}
		
		if(yDirection == "down")
		{
			y+= enemyMoveSpeed;
			if(y > points[0].y)
			{
				y = points[0].y;
				yDirection = "d";
			}
		}
		
		if(x == points[0].x && y == points[0].y)
		{
			RemovePoint();
			if(points.size() <= 0)
			{
				SetHomePosition();
			}
		}
	}
}

void enemy::SetHomePosition()
{
	int tempX = 120 + (enemyGridPositionX * 52);
	int tempY = 20 + (enemyGridPositionY * 45);
	
	if(enemyGridPositionX == -1 || enemyGridPositionY == -1)
	{
		tempY = 650;
		tempX = rand() % 32 +(playerObj->x - 16);
	}
	
	if(x < tempX)
	{
		xDirection = "right";
	}
	else
	{
		xDirection = "left";
	}
	
	if(y < tempY)
	{
		yDirection  = "down";
	}
	else
	{
		yDirection  = "up";
	}
}

void enemy::Shoot()
{
	if(health> 0)
	{
		if(shootTime.size() > 0)
		{
			if(shootTime[0] > 0)
			{
				shootTime[0]--;
				if(shootTime[0] == 0)
				{
					listOfEnemyBulletsObj.push_back(new enemyBullets(x + 16, y + 32));
					shootTime.erase(shootTime.begin() + 0);
					PlaySound(enemyShotSnd);
				}
			}
		}
	}
}

void enemy::Launch()
{
	if(enemyType == 1)
	{
		points.push_back(gameManagerObj->SetPoint(344,287));
		points.push_back(gameManagerObj->SetPoint(rand() % 64 + playerObj->x,350));	
		points.push_back(gameManagerObj->SetPoint(rand() % 64 + (playerObj->x - 64),400));	
		points.push_back(gameManagerObj->SetPoint(playerObj->x,700));	
	}
	
	if(enemyType >= 2 && enemyType<= 3)
	{
		int randomNumber = rand() %2;
		
		if(randomNumber == 0)
		{
			points.push_back(gameManagerObj->SetPoint(588,287));
			points.push_back(gameManagerObj->SetPoint(64,287));
			points.push_back(gameManagerObj->SetPoint(344,464));
			points.push_back(gameManagerObj->SetPoint(344,700));
			shootTime.push_back(120);
			
		}
		else
		{
		 	points.push_back(gameManagerObj->SetPoint(100,287));
			points.push_back(gameManagerObj->SetPoint(624,287));
			points.push_back(gameManagerObj->SetPoint(344,464));
			points.push_back(gameManagerObj->SetPoint(344,700));
			shootTime.push_back(120);
		}
	}
	
	if(enemyType >= 4)
	{
		int randomNumber = rand() %4;
		if(randomNumber == 0)
		{
			points.push_back(gameManagerObj->SetPoint(588,287));
			points.push_back(gameManagerObj->SetPoint(64,287));
			points.push_back(gameManagerObj->SetPoint(344,464));
			points.push_back(gameManagerObj->SetPoint(344,700));
			shootTime.push_back(140);
			
		}
		else if(randomNumber == 1)
		{
		 	points.push_back(gameManagerObj->SetPoint(100,287));
			points.push_back(gameManagerObj->SetPoint(624,287));
			points.push_back(gameManagerObj->SetPoint(344,464));
			points.push_back(gameManagerObj->SetPoint(344,700));
			shootTime.push_back(140);
		}
		else if(randomNumber == 2)
		{
			points.push_back(gameManagerObj->SetPoint(344,287));
			points.push_back(gameManagerObj->SetPoint(672,416));
			points.push_back(gameManagerObj->SetPoint(48,464));
			points.push_back(gameManagerObj->SetPoint(160,320));
			points.push_back(gameManagerObj->SetPoint(448,700));
			
			shootTime.push_back(80);
			shootTime.push_back(120);
		}
		else
		{
			if(enemyGridPositionX <= 4)
			{
				points.push_back(gameManagerObj->SetPoint(164,287));
				points.push_back(gameManagerObj->SetPoint(32,384));
				points.push_back(gameManagerObj->SetPoint(300,440));
				points.push_back(gameManagerObj->SetPoint(160,700));
				shootTime.push_back(40);
				shootTime.push_back(140);
			}
			
			else
			{
				points.push_back(gameManagerObj->SetPoint(524,287));
				points.push_back(gameManagerObj->SetPoint(392,384));
				points.push_back(gameManagerObj->SetPoint(660,440));
				points.push_back(gameManagerObj->SetPoint(520,700));
				shootTime.push_back(40);
				shootTime.push_back(140);
			}
		}
		
	}
	
	if(points.size() > 0)
	{
		if(x < points[0].x)
		{
			xDirection = "right";
		}
		else
		{
			xDirection = "left";
		}
		
		if(y < points[0].y)
		{
			yDirection = "down";
		}
		else
		{
			yDirection = "up";
		}
		
	}
}

void enemy::ResetY()
{
	
	
	if(y >= 650)
	{
		if(enemyGridPositionY == -1 || enemyGridPositionX == -1)
		{
			isDead = true;
			return;
		}
		
		points.clear();
		y = -20;
	}
}

void enemy::Rotate()
{
	float goalPosition = 0;
	
	if(xDirection == "left")
	{
		if(yDirection == "up")
		{
			goalPosition = 2.33874f;
		}
		else if(yDirection == "down")
		{
			goalPosition = 0.785398f;
		}
		else
		{
			goalPosition = 1.5708f;
		}
	}
	else if(xDirection == "right")
	{
		if(yDirection == "up")
		{
			goalPosition = 3.92699f;
		}
		else if(yDirection == "down")
		{
			goalPosition = 5.49779f;
		}
		else
		{
			goalPosition = 4.71239f;
		}
	}
	else
	{
		if(yDirection == "up")
		{
			goalPosition = 3.14159f;
		}
		else if(yDirection == "down")
		{
			goalPosition = 0.0f;
		}
		else
		{
			goalPosition = 0.0f;
		}
	}
	
	
	if(angle != goalPosition)
	{
		float leftDistance  = 0;
		float rightDistance = 0;
		
		if(goalPosition < angle)
		{
			leftDistance  = (RAD * 360) - angle + goalPosition;
			rightDistance = angle - goalPosition;
		}
		else
		{
			leftDistance = goalPosition - angle;
			rightDistance = (RAD * 360) - goalPosition + angle;
		}
		
			
			
		
		if(leftDistance <= rightDistance)
		{
			angle += (RAD*6);
			if(angle >= 6.28319f)
			{
				angle = angle - 6.28319f;
			}
			
			if(angle >= goalPosition && angle <= goalPosition + (RAD*6) )
			{
				angle = goalPosition;
			}
		}
		else
		{
			angle -= (RAD*6);
			if(angle < 0)
			{
				angle = 6.28319 + angle;
			}
			
			if(angle <= goalPosition && angle >= goalPosition - (RAD*6) )
			{
				angle = goalPosition;
			}
		}
	}
	
	
}

void enemy::Draw()
{
	//vita2d_draw_rectangle(x, y, 32, 32, RGBA8(255,0,0,255));	
	vita2d_draw_texture_part_scale_rotate(spriteTexture, x + 16, y + 16, enemyType * 32, 0, 32,32,1,1,angle);
}

bool enemy::Update()
{

	Move();
	Rotate();
	CheckHealth();
	ResetY();
	Shoot();
	return isDead;
}