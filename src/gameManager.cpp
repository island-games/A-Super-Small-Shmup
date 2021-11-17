#include "gameManager.h"
#include "objectHolder.h"


gameManager::gameManager()
{
	logString = "";
	waveState = "ready";
	nextEnemySpawnTimer = 0;
	enemyWave = 0;
	readyTimer = 0;
	wave = 3;
	enemyLaunchTime = 0;
	listOfEnemiesInWave;
	doubleRow = false;
	fullGridMove = false;
	canGetBonus = false;
	pathToFollow2;
	pathToFollow;
	bonusScore = 0;
	ufoGeneratorTime = 0;
	hasFiredShot = false;
}

void gameManager::Ready()
{
	readyTimer++;
	if(readyTimer > 90)
	{
		waveState = "game";
		readyTimer = 0;
	}
}

void gameManager::RespawnPlayer()
{
	if(readyTimer > 60)
	{
		if(playerObj != NULL)
		{
			playerObj->Respawn();
		}
		readyTimer = 0;
		waveState = "game";
	}
}

void gameManager::CreateEnemy()
{
	nextEnemySpawnTimer--;
	
	if(nextEnemySpawnTimer <= 0 && listOfEnemiesInWave.size() > 0)
	{
		//int xPos, int yPos, int tempType, int enemyGridPositionTempx, int enemyGridPositionTempy std::vector<Vector2> listOfPoints
		listOfEnemyObj.push_back(new enemy(pathToFollow[0].x, pathToFollow[0].y,
		listOfEnemiesInWave[0].enemyType, listOfEnemiesInWave[0].xPos, listOfEnemiesInWave[0].yPos,
		pathToFollow,listOfEnemiesInWave[0].shootWhileEntering));
		listOfEnemiesInWave.erase(listOfEnemiesInWave.begin() + 0);
		nextEnemySpawnTimer = 18;
		
		if(doubleRow == true)
		{
			if(listOfEnemiesInWave.size() > 0)
			{
				listOfEnemyObj.push_back(new enemy(pathToFollow2[0].x, pathToFollow2[0].y,
				listOfEnemiesInWave[0].enemyType, listOfEnemiesInWave[0].xPos, listOfEnemiesInWave[0].yPos,
				pathToFollow2,listOfEnemiesInWave[0].shootWhileEntering));
				listOfEnemiesInWave.erase(listOfEnemiesInWave.begin() + 0);
			}
		}

	}
	
	else if(listOfEnemiesInWave.size() <= 0)
	{
		if(CheckInPosition() == true)
		{
			enemyWave++;
			SetPatternForWave();
			nextEnemySpawnTimer = 18;

		}
	}
}

gameManager::preenemy gameManager::CreatePreenemy(int tempX, int tempY, int typeTemp)
{
	preenemy tempEnemy;
	tempEnemy.xPos = tempX;
	tempEnemy.yPos = tempY;
	tempEnemy.enemyType = typeTemp;
	tempEnemy.shootWhileEntering = false;
	
	return tempEnemy;
}

gameManager::preenemy gameManager::CreatePreenemy(int tempX, int tempY, int typeTemp, bool tempShootWhileEntering)
{
	preenemy tempEnemy;
	tempEnemy.xPos = tempX;
	tempEnemy.yPos = tempY;
	tempEnemy.enemyType = typeTemp;
	tempEnemy.shootWhileEntering = tempShootWhileEntering;
	
	return tempEnemy;
}

bool gameManager::CheckInPosition()
{
	bool tempPosition = true;
	
	for(int i = 0; i < listOfEnemyObj.size(); i++)
	{
		if(listOfEnemyObj[i]->inPosition == false)
		{
			return false;
		}
	}
	
	if(canGetBonus == true)
	{
		AddBonus();
	}
	
	return tempPosition;
}

void gameManager::AddBonus()
{
	PlaySound(bonusSnd);
	score += bonusScore;
	Bartender_UnlockTrophy(7);
}

void gameManager::SetPatternForWave()
{
	pathToFollow = GetTravelPath(enemyWave);
	pathToFollow2 = GetTravelPath2(enemyWave);
		std::string waveLayout = "";
		doubleRow = false;
		canGetBonus = true;
	switch(wave)
	{
		case 1:
				if(enemyWave == 1)
				{
					
					listOfEnemiesInWave.push_back(CreatePreenemy(2,3,1));
					listOfEnemiesInWave.push_back(CreatePreenemy(3,3,1));
					listOfEnemiesInWave.push_back(CreatePreenemy(4,3,1));
					listOfEnemiesInWave.push_back(CreatePreenemy(2,2,2));
					listOfEnemiesInWave.push_back(CreatePreenemy(3,2,2));
					bonusScore = 500;
					
					
				}
				
				if(enemyWave == 2)
				{
					
					listOfEnemiesInWave.push_back(CreatePreenemy(7,3,1));
					listOfEnemiesInWave.push_back(CreatePreenemy(6,3,1));
					listOfEnemiesInWave.push_back(CreatePreenemy(5,3,1));
					listOfEnemiesInWave.push_back(CreatePreenemy(7,2,2));
					listOfEnemiesInWave.push_back(CreatePreenemy(6,2,2));
					bonusScore = 500;
				}
				
				if(enemyWave == 3)
				{
					
					listOfEnemiesInWave.push_back(CreatePreenemy(4,2,2));
					listOfEnemiesInWave.push_back(CreatePreenemy(3,1,3));
					listOfEnemiesInWave.push_back(CreatePreenemy(4,1,3,true));
					listOfEnemiesInWave.push_back(CreatePreenemy(5,1,3));
					listOfEnemiesInWave.push_back(CreatePreenemy(5,2,2));
					bonusScore = 1000;
				}
				
				if(enemyWave == 4)
				{
					
					listOfEnemiesInWave.push_back(CreatePreenemy(4,0,4));
					listOfEnemiesInWave.push_back(CreatePreenemy(3,0,3));
					listOfEnemiesInWave.push_back(CreatePreenemy(6,0,3,true));
					listOfEnemiesInWave.push_back(CreatePreenemy(6,1,3));
					listOfEnemiesInWave.push_back(CreatePreenemy(5,0,4));
					bonusScore = 1000;
				}
				
				if(enemyWave == 5)
				{
					enemyWave = 6;
				}
				
		break;
		
		
		case 2:
			
			if(enemyWave == 1)
				{
					doubleRow = true;
					listOfEnemiesInWave.push_back(CreatePreenemy(4,4,1));
					listOfEnemiesInWave.push_back(CreatePreenemy(2,3,1));
					listOfEnemiesInWave.push_back(CreatePreenemy(3,3,1));
					listOfEnemiesInWave.push_back(CreatePreenemy(4,3,2));
					listOfEnemiesInWave.push_back(CreatePreenemy(2,2,2,true));
					listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,1));
					bonusScore = 600;
					
				}
				
				if(enemyWave == 2)
				{
					
					listOfEnemiesInWave.push_back(CreatePreenemy(5,4,1));
					listOfEnemiesInWave.push_back(CreatePreenemy(7,3,1));
					listOfEnemiesInWave.push_back(CreatePreenemy(6,3,1));
					listOfEnemiesInWave.push_back(CreatePreenemy(5,3,2,true));
					listOfEnemiesInWave.push_back(CreatePreenemy(7,2,2));
					bonusScore = 500;
				}
				
				if(enemyWave == 3)
				{
					
					listOfEnemiesInWave.push_back(CreatePreenemy(4,2,2));
					listOfEnemiesInWave.push_back(CreatePreenemy(3,2,2));
					listOfEnemiesInWave.push_back(CreatePreenemy(5,0,4,true));
					listOfEnemiesInWave.push_back(CreatePreenemy(6,0,4));
					listOfEnemiesInWave.push_back(CreatePreenemy(7,1,3));
					bonusScore = 1000;
				}
				
				if(enemyWave == 4)
				{
					doubleRow = true;
					listOfEnemiesInWave.push_back(CreatePreenemy(6,2,2));
					listOfEnemiesInWave.push_back(CreatePreenemy(5,2,2));
					listOfEnemiesInWave.push_back(CreatePreenemy(3,0,4));
					listOfEnemiesInWave.push_back(CreatePreenemy(4,0,4));
					listOfEnemiesInWave.push_back(CreatePreenemy(2,1,3,true));
					listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,3));
					bonusScore = 1000;
				}
				
				if(enemyWave == 5)
				{
					
					listOfEnemiesInWave.push_back(CreatePreenemy(3,1,3,true));
					listOfEnemiesInWave.push_back(CreatePreenemy(4,1,3));
					listOfEnemiesInWave.push_back(CreatePreenemy(5,1,3));
					listOfEnemiesInWave.push_back(CreatePreenemy(6,1,3,true));
					bonusScore = 750;
				}
			
		break;
		
		
		case 3:

			if(enemyWave == 1)
				{
					doubleRow = true;
					listOfEnemiesInWave.push_back(CreatePreenemy(3,4,1));
					listOfEnemiesInWave.push_back(CreatePreenemy(4,4,1));
					listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,2));
					listOfEnemiesInWave.push_back(CreatePreenemy(2,3,1));
					listOfEnemiesInWave.push_back(CreatePreenemy(1,3,1));
					listOfEnemiesInWave.push_back(CreatePreenemy(4,3,2,true));
					bonusScore = 750;
					
				}				
				if(enemyWave == 2)
				{
					listOfEnemiesInWave.push_back(CreatePreenemy(6,4,1));
					listOfEnemiesInWave.push_back(CreatePreenemy(5,4,1));
					listOfEnemiesInWave.push_back(CreatePreenemy(7,3,1));
					listOfEnemiesInWave.push_back(CreatePreenemy(8,3,1));
					listOfEnemiesInWave.push_back(CreatePreenemy(5,3,2,true));
					bonusScore = 750;
				}			
				if(enemyWave == 3)
				{
					listOfEnemiesInWave.push_back(CreatePreenemy(6,3,2));
					listOfEnemiesInWave.push_back(CreatePreenemy(2,2,2));
					listOfEnemiesInWave.push_back(CreatePreenemy(3,2,2,true));
					listOfEnemiesInWave.push_back(CreatePreenemy(4,2,2));
					listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,3));
					listOfEnemiesInWave.push_back(CreatePreenemy(5,1,3));
					bonusScore = 1000;
				}			
				if(enemyWave == 4)
				{
					listOfEnemiesInWave.push_back(CreatePreenemy(3,3,2,true));
					listOfEnemiesInWave.push_back(CreatePreenemy(7,2,2));
					listOfEnemiesInWave.push_back(CreatePreenemy(6,2,2));
					listOfEnemiesInWave.push_back(CreatePreenemy(5,2,2));
					listOfEnemiesInWave.push_back(CreatePreenemy(4,1,3));
					bonusScore = 800;
				}	
				if(enemyWave == 5)
				{
					
					listOfEnemiesInWave.push_back(CreatePreenemy(2,1,3));
					listOfEnemiesInWave.push_back(CreatePreenemy(7,1,3));
					listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,3));
					listOfEnemiesInWave.push_back(CreatePreenemy(3,1,3));
					listOfEnemiesInWave.push_back(CreatePreenemy(6,1,3));
					listOfEnemiesInWave.push_back(CreatePreenemy(4,0,5,true));
					listOfEnemiesInWave.push_back(CreatePreenemy(5,0,5));
					listOfEnemiesInWave.push_back(CreatePreenemy(3,0,4));
					listOfEnemiesInWave.push_back(CreatePreenemy(6,0,4));
					listOfEnemiesInWave.push_back(CreatePreenemy(2,0,4));
					listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,5));
					listOfEnemiesInWave.push_back(CreatePreenemy(7,0,4));
					doubleRow = true;
					bonusScore = 1500;
				}
			
		break;
		
		
		case 4:
			
		   if(enemyWave == 1)
				{
					listOfEnemiesInWave.push_back(CreatePreenemy(0,4,1));
					listOfEnemiesInWave.push_back(CreatePreenemy(9,4,1));
					listOfEnemiesInWave.push_back(CreatePreenemy(1,4,1));
					listOfEnemiesInWave.push_back(CreatePreenemy(8,4,1));
					listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,1));
					listOfEnemiesInWave.push_back(CreatePreenemy(2,4,1));
					listOfEnemiesInWave.push_back(CreatePreenemy(7,4,1));
					listOfEnemiesInWave.push_back(CreatePreenemy(3,4,1));
					listOfEnemiesInWave.push_back(CreatePreenemy(6,4,1));
					listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,1));
					listOfEnemiesInWave.push_back(CreatePreenemy(4,4,1));
					listOfEnemiesInWave.push_back(CreatePreenemy(5,4,1));					
					doubleRow = true;
					bonusScore = 1000;
				}
				if(enemyWave == 2)
				{
					listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,2));
					listOfEnemiesInWave.push_back(CreatePreenemy(1,3,1));
					listOfEnemiesInWave.push_back(CreatePreenemy(8,3,1));
					listOfEnemiesInWave.push_back(CreatePreenemy(4,3,2));
					listOfEnemiesInWave.push_back(CreatePreenemy(5,3,2,true));
					listOfEnemiesInWave.push_back(CreatePreenemy(3,3,2));
					listOfEnemiesInWave.push_back(CreatePreenemy(6,3,2));
					listOfEnemiesInWave.push_back(CreatePreenemy(2,3,2));
					listOfEnemiesInWave.push_back(CreatePreenemy(7,3,2));
					bonusScore = 1500;
					
				}		
				if(enemyWave == 3)
				{
					listOfEnemiesInWave.push_back(CreatePreenemy(2,1,3));
					listOfEnemiesInWave.push_back(CreatePreenemy(7,1,3));
					listOfEnemiesInWave.push_back(CreatePreenemy(3,1,4,true));
					listOfEnemiesInWave.push_back(CreatePreenemy(5,1,4));
					listOfEnemiesInWave.push_back(CreatePreenemy(4,1,4));
					listOfEnemiesInWave.push_back(CreatePreenemy(6,1,4));
					bonusScore = 1000;
					
				}
				
				if(enemyWave == 4)
				{
					listOfEnemiesInWave.push_back(CreatePreenemy(2,2,2));
					listOfEnemiesInWave.push_back(CreatePreenemy(7,2,2));
					listOfEnemiesInWave.push_back(CreatePreenemy(3,2,3));
					listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,3));
					listOfEnemiesInWave.push_back(CreatePreenemy(6,2,3,true));
					listOfEnemiesInWave.push_back(CreatePreenemy(5,2,3));
					listOfEnemiesInWave.push_back(CreatePreenemy(4,2,3));
					listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,3,true));
					bonusScore = 1500;
				}
				
				if(enemyWave == 5)
				{
					listOfEnemiesInWave.push_back(CreatePreenemy(4,0,5,true));
					listOfEnemiesInWave.push_back(CreatePreenemy(5,0,5));
					listOfEnemiesInWave.push_back(CreatePreenemy(6,0,5));
					listOfEnemiesInWave.push_back(CreatePreenemy(3,0,5));
					listOfEnemiesInWave.push_back(CreatePreenemy(7,0,4));
					listOfEnemiesInWave.push_back(CreatePreenemy(2,0,4,true));
					doubleRow = true;
					bonusScore = 2000;
				}
		   
		break;
		
		case 5:
		   
		   if(enemyWave == 1)
		   {
			   listOfEnemiesInWave.push_back(CreatePreenemy(2,1,3,true));
			   listOfEnemiesInWave.push_back(CreatePreenemy(7,1,3));
			   listOfEnemiesInWave.push_back(CreatePreenemy(3,1,4));
			   listOfEnemiesInWave.push_back(CreatePreenemy(6,1,4));
			   listOfEnemiesInWave.push_back(CreatePreenemy(4,1,4));
			   listOfEnemiesInWave.push_back(CreatePreenemy(5,1,4));
			   listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,5));
			   listOfEnemiesInWave.push_back(CreatePreenemy(3,0,5));
			   listOfEnemiesInWave.push_back(CreatePreenemy(6,0,5));
			   listOfEnemiesInWave.push_back(CreatePreenemy(4,0,5));
			   listOfEnemiesInWave.push_back(CreatePreenemy(5,0,5,true));
			   listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,5));			   
			   doubleRow = true;
			   bonusScore = 3000;
		   }
		   if(enemyWave == 2)
		   {
			   listOfEnemiesInWave.push_back(CreatePreenemy(0,4,1));
			   listOfEnemiesInWave.push_back(CreatePreenemy(0,3,2));
			   listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,2,true));
			   listOfEnemiesInWave.push_back(CreatePreenemy(1,4,1));
			   listOfEnemiesInWave.push_back(CreatePreenemy(1,3,2));
			   listOfEnemiesInWave.push_back(CreatePreenemy(2,4,1));
			   listOfEnemiesInWave.push_back(CreatePreenemy(2,3,2,true));
			   listOfEnemiesInWave.push_back(CreatePreenemy(3,4,1));
			   listOfEnemiesInWave.push_back(CreatePreenemy(3,3,2));
			   listOfEnemiesInWave.push_back(CreatePreenemy(4,4,1));
			   listOfEnemiesInWave.push_back(CreatePreenemy(4,3,2));
			   listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,1));
			   bonusScore = 1500;
		   }
		   if(enemyWave == 3)
		   {
			   listOfEnemiesInWave.push_back(CreatePreenemy(9,4,1));
			   listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,2,true));
			   listOfEnemiesInWave.push_back(CreatePreenemy(9,3,2));
			   listOfEnemiesInWave.push_back(CreatePreenemy(8,4,1));
			   listOfEnemiesInWave.push_back(CreatePreenemy(8,3,2));
			   listOfEnemiesInWave.push_back(CreatePreenemy(7,4,1));
			   listOfEnemiesInWave.push_back(CreatePreenemy(7,3,2,true));
			   listOfEnemiesInWave.push_back(CreatePreenemy(6,4,1));
			   listOfEnemiesInWave.push_back(CreatePreenemy(6,3,2));
			   listOfEnemiesInWave.push_back(CreatePreenemy(5,4,1));
			   listOfEnemiesInWave.push_back(CreatePreenemy(5,3,2));
			   listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,1));
			   doubleRow = true;
			   bonusScore = 1500;
		   }
		   if(enemyWave == 4)
		   {
			   listOfEnemiesInWave.push_back(CreatePreenemy(2,0,4,true));
			   listOfEnemiesInWave.push_back(CreatePreenemy(1,2,2));
			   listOfEnemiesInWave.push_back(CreatePreenemy(2,2,2));
			   listOfEnemiesInWave.push_back(CreatePreenemy(3,2,3));
			   listOfEnemiesInWave.push_back(CreatePreenemy(4,2,3));
			   bonusScore = 1000;
		   }
		   if(enemyWave == 5)
		   {
			   listOfEnemiesInWave.push_back(CreatePreenemy(7,0,4));
			   listOfEnemiesInWave.push_back(CreatePreenemy(8,2,2));
			   listOfEnemiesInWave.push_back(CreatePreenemy(7,2,2));
			   listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,2));
			   listOfEnemiesInWave.push_back(CreatePreenemy(6,2,3));
			   listOfEnemiesInWave.push_back(CreatePreenemy(5,2,3,true));
			   doubleRow = true;
			   bonusScore = 1000;
		   }
		      
		break;
		
		case 6:

		   if(enemyWave == 1)
		   {
			   listOfEnemiesInWave.push_back(CreatePreenemy(4,4,1));
			   listOfEnemiesInWave.push_back(CreatePreenemy(5,4,1));
			   listOfEnemiesInWave.push_back(CreatePreenemy(4,3,2));
			   listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,2));
			   listOfEnemiesInWave.push_back(CreatePreenemy(5,3,2));
			   listOfEnemiesInWave.push_back(CreatePreenemy(4,2,3,true));
			   listOfEnemiesInWave.push_back(CreatePreenemy(5,2,3));
			   listOfEnemiesInWave.push_back(CreatePreenemy(4,1,4));
			   listOfEnemiesInWave.push_back(CreatePreenemy(5,1,4));
			   listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,4));
			   listOfEnemiesInWave.push_back(CreatePreenemy(4,0,5));
			   listOfEnemiesInWave.push_back(CreatePreenemy(5,0,5));
			   doubleRow = true;
			   bonusScore = 1500;
		   }
		   if(enemyWave == 2)
		   {
			   listOfEnemiesInWave.push_back(CreatePreenemy(0,4,1));
			   listOfEnemiesInWave.push_back(CreatePreenemy(1,4,1));
			   listOfEnemiesInWave.push_back(CreatePreenemy(2,4,1));
			   listOfEnemiesInWave.push_back(CreatePreenemy(3,4,1));
			   listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,2,true));
			   listOfEnemiesInWave.push_back(CreatePreenemy(6,4,1));
			   listOfEnemiesInWave.push_back(CreatePreenemy(7,4,1));
			   listOfEnemiesInWave.push_back(CreatePreenemy(8,4,1));
			   listOfEnemiesInWave.push_back(CreatePreenemy(9,4,1));
			   listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,3));
			   bonusScore = 2000;
			   doubleRow = true;
		   }
		   if(enemyWave == 3)
		   {
			   listOfEnemiesInWave.push_back(CreatePreenemy(0,3,2));
			   listOfEnemiesInWave.push_back(CreatePreenemy(1,3,2));
			   listOfEnemiesInWave.push_back(CreatePreenemy(2,3,2));
			   listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,2));
			   listOfEnemiesInWave.push_back(CreatePreenemy(3,3,2));
			   listOfEnemiesInWave.push_back(CreatePreenemy(0,2,3));
			   listOfEnemiesInWave.push_back(CreatePreenemy(1,2,3));
			   listOfEnemiesInWave.push_back(CreatePreenemy(2,2,3));
			   listOfEnemiesInWave.push_back(CreatePreenemy(3,2,3,true));
			   listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,3));
			   bonusScore = 2000;
		   }
		   if(enemyWave == 4)
		   {
			   listOfEnemiesInWave.push_back(CreatePreenemy(9,3,2));
			   listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,2));
			   listOfEnemiesInWave.push_back(CreatePreenemy(8,3,2));
			   listOfEnemiesInWave.push_back(CreatePreenemy(7,3,2));
			   listOfEnemiesInWave.push_back(CreatePreenemy(6,3,2,true));
			   listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,3));
			   listOfEnemiesInWave.push_back(CreatePreenemy(9,2,3));
			   listOfEnemiesInWave.push_back(CreatePreenemy(8,2,3));
			   listOfEnemiesInWave.push_back(CreatePreenemy(7,2,3));
			   listOfEnemiesInWave.push_back(CreatePreenemy(6,2,3));
			   doubleRow = true;
			   bonusScore = 2000;
		   }
		   if(enemyWave == 5)
		   {
			   listOfEnemiesInWave.push_back(CreatePreenemy(2,0,4));
			   listOfEnemiesInWave.push_back(CreatePreenemy(3,0,5));
			   listOfEnemiesInWave.push_back(CreatePreenemy(2,1,4));
			   listOfEnemiesInWave.push_back(CreatePreenemy(3,1,4));
			   listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,4));
			   listOfEnemiesInWave.push_back(CreatePreenemy(6,0,5,true));
			   listOfEnemiesInWave.push_back(CreatePreenemy(7,0,4));
			   listOfEnemiesInWave.push_back(CreatePreenemy(6,1,4));
			   listOfEnemiesInWave.push_back(CreatePreenemy(7,1,4));
			   bonusScore = 2000;
			   
		   }
		   
		break;
		
		case 7:

		   
			if(enemyWave == 1)
			{
				listOfEnemiesInWave.push_back(CreatePreenemy(2,0,5));
				listOfEnemiesInWave.push_back(CreatePreenemy(3,0,5));
				listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,5));
				listOfEnemiesInWave.push_back(CreatePreenemy(4,0,5,true));
				listOfEnemiesInWave.push_back(CreatePreenemy(5,0,5));
				listOfEnemiesInWave.push_back(CreatePreenemy(6,0,5));
				listOfEnemiesInWave.push_back(CreatePreenemy(7,0,5));
				listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,4));
				listOfEnemiesInWave.push_back(CreatePreenemy(3,1,4));
				listOfEnemiesInWave.push_back(CreatePreenemy(4,1,4,true));
				listOfEnemiesInWave.push_back(CreatePreenemy(6,1,4));
				listOfEnemiesInWave.push_back(CreatePreenemy(7,1,4));
				doubleRow = true;
				bonusScore = 4000;
			}
			if(enemyWave == 2)
			{
				listOfEnemiesInWave.push_back(CreatePreenemy(0,1,4));
				listOfEnemiesInWave.push_back(CreatePreenemy(1,1,4));
				listOfEnemiesInWave.push_back(CreatePreenemy(2,1,4,true));
				listOfEnemiesInWave.push_back(CreatePreenemy(7,1,4));
				listOfEnemiesInWave.push_back(CreatePreenemy(8,1,4));
				listOfEnemiesInWave.push_back(CreatePreenemy(9,1,4));
				listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,4));
				listOfEnemiesInWave.push_back(CreatePreenemy(0,2,3));
				listOfEnemiesInWave.push_back(CreatePreenemy(0,3,2));
				listOfEnemiesInWave.push_back(CreatePreenemy(9,2,3));
				listOfEnemiesInWave.push_back(CreatePreenemy(9,3,2,true));
				bonusScore = 4000;
			}
			if(enemyWave == 3)
			{
				listOfEnemiesInWave.push_back(CreatePreenemy(0,4,1));
				listOfEnemiesInWave.push_back(CreatePreenemy(1,4,1));
				listOfEnemiesInWave.push_back(CreatePreenemy(2,4,1));
				listOfEnemiesInWave.push_back(CreatePreenemy(3,4,1));
				listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,1));
				listOfEnemiesInWave.push_back(CreatePreenemy(4,4,1));
				listOfEnemiesInWave.push_back(CreatePreenemy(5,4,1));
				listOfEnemiesInWave.push_back(CreatePreenemy(6,4,1));
				listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,1));
				listOfEnemiesInWave.push_back(CreatePreenemy(7,4,1));
				listOfEnemiesInWave.push_back(CreatePreenemy(8,4,1));
				listOfEnemiesInWave.push_back(CreatePreenemy(9,4,1));
				doubleRow = true;
				bonusScore = 2000;
			}
			if(enemyWave == 4)
			{
				listOfEnemiesInWave.push_back(CreatePreenemy(1,3,2,true));
				listOfEnemiesInWave.push_back(CreatePreenemy(2,3,2));
				listOfEnemiesInWave.push_back(CreatePreenemy(1,2,3));
				listOfEnemiesInWave.push_back(CreatePreenemy(2,2,3));
				listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,2));
				listOfEnemiesInWave.push_back(CreatePreenemy(8,3,2));
				listOfEnemiesInWave.push_back(CreatePreenemy(7,3,2));
				listOfEnemiesInWave.push_back(CreatePreenemy(8,2,3));
				listOfEnemiesInWave.push_back(CreatePreenemy(7,2,3,true));
				listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,3));
				bonusScore = 4000;
				doubleRow = true;
			}
			if(enemyWave == 5)
			{
				listOfEnemiesInWave.push_back(CreatePreenemy(3,3,2));
				listOfEnemiesInWave.push_back(CreatePreenemy(4,3,2));
				listOfEnemiesInWave.push_back(CreatePreenemy(5,3,2));
				listOfEnemiesInWave.push_back(CreatePreenemy(6,3,2,true));
				listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,3));
				listOfEnemiesInWave.push_back(CreatePreenemy(6,2,3));
				listOfEnemiesInWave.push_back(CreatePreenemy(5,2,3));
				listOfEnemiesInWave.push_back(CreatePreenemy(4,2,3));
				listOfEnemiesInWave.push_back(CreatePreenemy(3,2,3,true));
				bonusScore = 3000;
			}
			
		break;
		
		case 8:
		   
		   if(enemyWave == 1)
			{
				listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,1));
				listOfEnemiesInWave.push_back(CreatePreenemy(0,4,1));
				listOfEnemiesInWave.push_back(CreatePreenemy(1,4,1));
				listOfEnemiesInWave.push_back(CreatePreenemy(2,4,1));
				listOfEnemiesInWave.push_back(CreatePreenemy(3,4,1));
				listOfEnemiesInWave.push_back(CreatePreenemy(4,4,1));
				listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,1));
				listOfEnemiesInWave.push_back(CreatePreenemy(5,4,1));
				listOfEnemiesInWave.push_back(CreatePreenemy(6,4,1));
				listOfEnemiesInWave.push_back(CreatePreenemy(7,4,1));
				listOfEnemiesInWave.push_back(CreatePreenemy(8,4,1));
				listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,1));
				listOfEnemiesInWave.push_back(CreatePreenemy(9,4,1));
				doubleRow = true;
				bonusScore = 3000;
			}
			if(enemyWave == 2)
			{
				listOfEnemiesInWave.push_back(CreatePreenemy(0,3,2));
				listOfEnemiesInWave.push_back(CreatePreenemy(1,3,2));
				listOfEnemiesInWave.push_back(CreatePreenemy(2,3,2));
				listOfEnemiesInWave.push_back(CreatePreenemy(3,3,2,true));
				listOfEnemiesInWave.push_back(CreatePreenemy(4,3,2));
				listOfEnemiesInWave.push_back(CreatePreenemy(5,3,2));
				listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,2));
				listOfEnemiesInWave.push_back(CreatePreenemy(6,3,2));
				listOfEnemiesInWave.push_back(CreatePreenemy(7,3,2));
				listOfEnemiesInWave.push_back(CreatePreenemy(8,3,2,true));
				listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,2));
				listOfEnemiesInWave.push_back(CreatePreenemy(9,3,2));
				doubleRow = true;
				bonusScore = 3000;
			}
			if(enemyWave == 3)
			{
				listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,4));
				listOfEnemiesInWave.push_back(CreatePreenemy(0,2,3));
				listOfEnemiesInWave.push_back(CreatePreenemy(1,2,3,true));
				listOfEnemiesInWave.push_back(CreatePreenemy(2,2,3));
				listOfEnemiesInWave.push_back(CreatePreenemy(3,2,3));
				listOfEnemiesInWave.push_back(CreatePreenemy(4,2,3));
				listOfEnemiesInWave.push_back(CreatePreenemy(5,2,3));
				listOfEnemiesInWave.push_back(CreatePreenemy(6,2,3));
				listOfEnemiesInWave.push_back(CreatePreenemy(7,2,3,true));
				listOfEnemiesInWave.push_back(CreatePreenemy(8,2,3));
				listOfEnemiesInWave.push_back(CreatePreenemy(9,2,3));
				listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,4));
				doubleRow = true;
				bonusScore = 4000;
			}
			if(enemyWave == 4)
			{
				listOfEnemiesInWave.push_back(CreatePreenemy(0,1,4,true));
				listOfEnemiesInWave.push_back(CreatePreenemy(1,1,4));
				listOfEnemiesInWave.push_back(CreatePreenemy(2,1,4));
				listOfEnemiesInWave.push_back(CreatePreenemy(3,1,4));
				listOfEnemiesInWave.push_back(CreatePreenemy(4,1,4));
				listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,4));
				listOfEnemiesInWave.push_back(CreatePreenemy(5,1,4));
				listOfEnemiesInWave.push_back(CreatePreenemy(6,1,4));
				listOfEnemiesInWave.push_back(CreatePreenemy(7,1,4));
				listOfEnemiesInWave.push_back(CreatePreenemy(8,1,4));
				listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,4));
				listOfEnemiesInWave.push_back(CreatePreenemy(9,1,4,true));
				doubleRow = true;
				bonusScore = 4000;
			}
			if(enemyWave == 5)
			{
				listOfEnemiesInWave.push_back(CreatePreenemy(0,0,5,true));
				listOfEnemiesInWave.push_back(CreatePreenemy(1,0,5));
				listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,5));
				listOfEnemiesInWave.push_back(CreatePreenemy(2,0,5));
				listOfEnemiesInWave.push_back(CreatePreenemy(3,0,5));
				listOfEnemiesInWave.push_back(CreatePreenemy(4,0,5,true));
				listOfEnemiesInWave.push_back(CreatePreenemy(5,0,5));
				listOfEnemiesInWave.push_back(CreatePreenemy(6,0,5));
				listOfEnemiesInWave.push_back(CreatePreenemy(7,0,5));
				listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,5));
				listOfEnemiesInWave.push_back(CreatePreenemy(8,0,5));
				listOfEnemiesInWave.push_back(CreatePreenemy(9,0,5,true));
				doubleRow = true;
				bonusScore = 5000;
			}
		break;
		
		case 9:
		   
		   if(enemyWave == 1)
		   {
			   listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,5));
			   listOfEnemiesInWave.push_back(CreatePreenemy(4,4,4));
			   listOfEnemiesInWave.push_back(CreatePreenemy(5,4,4));
			   listOfEnemiesInWave.push_back(CreatePreenemy(3,4,4,true));
			   listOfEnemiesInWave.push_back(CreatePreenemy(6,4,4));
			   listOfEnemiesInWave.push_back(CreatePreenemy(0,4,5));
			   listOfEnemiesInWave.push_back(CreatePreenemy(9,4,4));
			   listOfEnemiesInWave.push_back(CreatePreenemy(2,4,4));
			   listOfEnemiesInWave.push_back(CreatePreenemy(7,4,4,true));
			   listOfEnemiesInWave.push_back(CreatePreenemy(1,4,4));
			   listOfEnemiesInWave.push_back(CreatePreenemy(8,4,4));
			   listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,5));
			   doubleRow = true;
			   bonusScore = 5000;
		   }
		   if(enemyWave == 2)
		   {
			   listOfEnemiesInWave.push_back(CreatePreenemy(0,3,5,true));
			   listOfEnemiesInWave.push_back(CreatePreenemy(0,2,5));
			   listOfEnemiesInWave.push_back(CreatePreenemy(0,1,5));
			   listOfEnemiesInWave.push_back(CreatePreenemy(0,0,5));
			   listOfEnemiesInWave.push_back(CreatePreenemy(9,3,5));
			   listOfEnemiesInWave.push_back(CreatePreenemy(9,2,5,true));
			   listOfEnemiesInWave.push_back(CreatePreenemy(9,1,5));
			   listOfEnemiesInWave.push_back(CreatePreenemy(9,0,5));
			   listOfEnemiesInWave.push_back(CreatePreenemy(4,3,3));
			   listOfEnemiesInWave.push_back(CreatePreenemy(5,3,3,true));
			   doubleRow = true;
			   bonusScore = 5000;
		   }
		   if(enemyWave == 3)
		   {
			  listOfEnemiesInWave.push_back(CreatePreenemy(1,3,3));
			   listOfEnemiesInWave.push_back(CreatePreenemy(2,3,3));
			   listOfEnemiesInWave.push_back(CreatePreenemy(1,2,3,true));
			   listOfEnemiesInWave.push_back(CreatePreenemy(2,2,2));
			   listOfEnemiesInWave.push_back(CreatePreenemy(1,1,3));
			   listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,3));
			   listOfEnemiesInWave.push_back(CreatePreenemy(2,1,3));
			   listOfEnemiesInWave.push_back(CreatePreenemy(1,0,4));
			   listOfEnemiesInWave.push_back(CreatePreenemy(2,0,4));
			   listOfEnemiesInWave.push_back(CreatePreenemy(3,0,4,true));
			   listOfEnemiesInWave.push_back(CreatePreenemy(4,0,4)); 
			   listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,4));
			   doubleRow = true;
			   bonusScore = 5000;
		   }
		   
		   if(enemyWave == 4)
		   {
			   listOfEnemiesInWave.push_back(CreatePreenemy(8,3,3));
			   listOfEnemiesInWave.push_back(CreatePreenemy(7,3,3));
			   listOfEnemiesInWave.push_back(CreatePreenemy(8,2,3));
			   listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,3));
			   listOfEnemiesInWave.push_back(CreatePreenemy(7,2,2));
			   listOfEnemiesInWave.push_back(CreatePreenemy(8,1,3));
			   listOfEnemiesInWave.push_back(CreatePreenemy(7,1,3,true));
			   listOfEnemiesInWave.push_back(CreatePreenemy(8,0,4));
			   listOfEnemiesInWave.push_back(CreatePreenemy(7,0,4));
			   listOfEnemiesInWave.push_back(CreatePreenemy(6,0,4));
			   listOfEnemiesInWave.push_back(CreatePreenemy(5,0,4,true));
			   listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,4));
			   doubleRow = true;
			   bonusScore = 5000;
		   }
		   
		   if(enemyWave == 5)
		   {
			   listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,2));
			   listOfEnemiesInWave.push_back(CreatePreenemy(3,3,3));
			   listOfEnemiesInWave.push_back(CreatePreenemy(6,3,3));
			   listOfEnemiesInWave.push_back(CreatePreenemy(4,2,2,true));
			   listOfEnemiesInWave.push_back(CreatePreenemy(5,2,2));
			   listOfEnemiesInWave.push_back(CreatePreenemy(4,1,3));
			   listOfEnemiesInWave.push_back(CreatePreenemy(5,1,3));
			   listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,3, true));
			   listOfEnemiesInWave.push_back(CreatePreenemy(3,1,3));
			   listOfEnemiesInWave.push_back(CreatePreenemy(3,2,2));
			   listOfEnemiesInWave.push_back(CreatePreenemy(6,1,3));
			   listOfEnemiesInWave.push_back(CreatePreenemy(6,2,2,true));
			   doubleRow;
			   bonusScore = 5000;
		   }
		   
		break;
		
		case 10:
			if(enemyWave == 1)
			{
				listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,1));
			   listOfEnemiesInWave.push_back(CreatePreenemy(0,4,1));
			   listOfEnemiesInWave.push_back(CreatePreenemy(1,4,1));
			   listOfEnemiesInWave.push_back(CreatePreenemy(2,4,1));
			   listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,1));
			   listOfEnemiesInWave.push_back(CreatePreenemy(3,4,1));
			   listOfEnemiesInWave.push_back(CreatePreenemy(4,4,1));
			   listOfEnemiesInWave.push_back(CreatePreenemy(5,4,1));
			   listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,1));
			   listOfEnemiesInWave.push_back(CreatePreenemy(6,4,1));
			   listOfEnemiesInWave.push_back(CreatePreenemy(7,4,1));
			   listOfEnemiesInWave.push_back(CreatePreenemy(8,4,1));
			   listOfEnemiesInWave.push_back(CreatePreenemy(9,4,1));
			   listOfEnemiesInWave.push_back(CreatePreenemy(-1,-1,1));
			   doubleRow = true;
			   bonusScore = 2000;
			   
			}
			
			if(enemyWave == 2)
			{
				listOfBossObj.push_back(new boss());
			   enemyWave = 6;
			}
		
			
		break;
					
	}
}

void gameManager::CheckIfWaveIsComplete()
{
	if(listOfEnemyObj.size() <= 0 && enemyWave >= 6 && listOfBossObj.size() <= 0 || wave == 0)
	{
		wave++;
		
		if(wave == 2)
		{
			Bartender_UnlockTrophy(1);
		}
		
		if(wave == 4)
		{
			Bartender_UnlockTrophy(2);
		}
		
		if(wave == 8)
		{
			Bartender_UnlockTrophy(3);
		}
		
		if(wave == 6 && playerObj != NULL)
		{
			if(playerObj->lives == 10)
			{
				Bartender_UnlockTrophy(9);
			}
				
		}
		
		enemyWave = 1;
		ufoGeneratorTime = 0;
		
		if(wave <= 3)
		{
			enemyMoveSpeed = 5;
		}
		else if(wave >= 4 && wave <= 6)
		{
			enemyMoveSpeed = 6;
		}
		else
		{
			enemyMoveSpeed = 7;
		}
		SetPatternForWave();
	}
}

void gameManager::EnemyMovement()
{
	if(fullGridMove == false)
	{
		totalGridOffsetDestination--;
		if(totalGridOffsetDestination <= -50)
		{
			totalGridOffsetDestination = -50;
			fullGridMove = true;
		}
	}
	else
	{
		totalGridOffsetDestination++;
		if(totalGridOffsetDestination >= 50)
		{
			totalGridOffsetDestination = 50;
			fullGridMove = false;
		}
	}
	
	
	
	if(columnResetTimer <= 0)
	{
		for(int i = 0; i < 9; i++)
		{
			int randomMovementColumn = rand() % 7;
			int posOrNeg = rand() % 2;
			
			if(posOrNeg == 0)
			{
				columnOffsetDestination[i] = -randomMovementColumn;
				
			}
			else
			{
				columnOffsetDestination[i] = randomMovementColumn;
			}
		}
		columnResetTimer = 300;
	}
	else
	{
		columnResetTimer--;
	}
}

Vector2 gameManager::SetPoint(int tempX, int tempY)
{
	Vector2 pointToReturn;
	pointToReturn.x = tempX;
	pointToReturn.y = tempY;
	
	return pointToReturn;
}

std::vector<Vector2> gameManager::GetTravelPath(int selectedPath)
{
std::vector<Vector2> tempToReturn;
	// Top Center
	if(selectedPath == 1)
	{
		tempToReturn.push_back(SetPoint(360,-40));
		tempToReturn.push_back(SetPoint(360, 48));
		tempToReturn.push_back(SetPoint(300,112));
		tempToReturn.push_back(SetPoint(22,192));
		tempToReturn.push_back(SetPoint(272,224));
		tempToReturn.push_back(SetPoint(256,352));
		tempToReturn.push_back(SetPoint(288,384));
		tempToReturn.push_back(SetPoint(352,400));
		tempToReturn.push_back(SetPoint(448,368));
		tempToReturn.push_back(SetPoint(480,304));
		
	}
	
	// Bottom Left
	if(selectedPath == 2)
	{
		tempToReturn.push_back(SetPoint(-16,496));
		tempToReturn.push_back(SetPoint(224 ,512));
		tempToReturn.push_back(SetPoint(608, 320));
		tempToReturn.push_back(SetPoint(592, 232));
		tempToReturn.push_back(SetPoint(512, 152));
		tempToReturn.push_back(SetPoint(408, 168));
		

	}
	
	// Bottom Right
	if(selectedPath == 3)
	{
		tempToReturn.push_back(SetPoint(750,496));
		tempToReturn.push_back(SetPoint(526, 512));
		tempToReturn.push_back(SetPoint(142, 320));
		tempToReturn.push_back(SetPoint(158,232));
		tempToReturn.push_back(SetPoint(238,152));
		tempToReturn.push_back(SetPoint(342,168));

	}
	
	// Top Left
	if(selectedPath == 4)
	{
		tempToReturn.push_back(SetPoint(-32,-32));
		tempToReturn.push_back(SetPoint(0,32));
		tempToReturn.push_back(SetPoint(128,112));
		tempToReturn.push_back(SetPoint(96,304));
		tempToReturn.push_back(SetPoint(432,272));
		tempToReturn.push_back(SetPoint(544,208));
		tempToReturn.push_back(SetPoint(528,112));
		tempToReturn.push_back(SetPoint(448,80));
		tempToReturn.push_back(SetPoint(368,128));

	}
	
	// Top Right
	if(selectedPath == 5)
	{
		tempToReturn.push_back(SetPoint(742,32));	
		tempToReturn.push_back(SetPoint(614,112));
		tempToReturn.push_back(SetPoint(646,304));
		tempToReturn.push_back(SetPoint(310,272));
		tempToReturn.push_back(SetPoint(198,208));
		tempToReturn.push_back(SetPoint(214,112));
		tempToReturn.push_back(SetPoint(294,80));
		tempToReturn.push_back(SetPoint(374,128));
		
	}
	
	
	return tempToReturn;
}


std::vector<Vector2> gameManager::GetTravelPath2(int selectedPath)
{
std::vector<Vector2> tempToReturn;
	// Top Center
	if(selectedPath == 1)
	{
		tempToReturn.push_back(SetPoint(400,-40));
		tempToReturn.push_back(SetPoint(400, 48));
		tempToReturn.push_back(SetPoint(328,140));
		tempToReturn.push_back(SetPoint(102,225));
		tempToReturn.push_back(SetPoint(314,202));
		tempToReturn.push_back(SetPoint(293,338));
		tempToReturn.push_back(SetPoint(312,370));
		tempToReturn.push_back(SetPoint(378,362));
		tempToReturn.push_back(SetPoint(427,329));
		tempToReturn.push_back(SetPoint(443,286));
		
	}
	
	// Bottom Left
	if(selectedPath == 2)
	{
		tempToReturn.push_back(SetPoint(-16,456));
		tempToReturn.push_back(SetPoint(222 ,472));
		tempToReturn.push_back(SetPoint(564, 280));
		tempToReturn.push_back(SetPoint(556, 242));
		tempToReturn.push_back(SetPoint(496, 187));
		tempToReturn.push_back(SetPoint(380, 205));
		
		

	}
	
	// Bottom Right
	if(selectedPath == 3)
	{
		tempToReturn.push_back(SetPoint(750,456));
		tempToReturn.push_back(SetPoint(520, 472));
		tempToReturn.push_back(SetPoint(178, 280));
		tempToReturn.push_back(SetPoint(162,242));
		tempToReturn.push_back(SetPoint(242,187));
		tempToReturn.push_back(SetPoint(362,205));
		
		
		


		
	}
	
	// Top Left
	if(selectedPath == 4)
	{
		tempToReturn.push_back(SetPoint(-32,-40));
		
		tempToReturn.push_back(SetPoint(0,68));
		tempToReturn.push_back(SetPoint(92,128));
		tempToReturn.push_back(SetPoint(53,337));
		tempToReturn.push_back(SetPoint(440,308));
		tempToReturn.push_back(SetPoint(578,226));
		tempToReturn.push_back(SetPoint(565,107));
		tempToReturn.push_back(SetPoint(446,50));
		tempToReturn.push_back(SetPoint(331,102));

	}
	
	// Top Right
	if(selectedPath == 5)
	{
		tempToReturn.push_back(SetPoint(742,68));	
		tempToReturn.push_back(SetPoint(650,128));
		tempToReturn.push_back(SetPoint(689,337));
		tempToReturn.push_back(SetPoint(302,308));
		tempToReturn.push_back(SetPoint(164,226));
		tempToReturn.push_back(SetPoint(177,107));
		tempToReturn.push_back(SetPoint(296,50));
		tempToReturn.push_back(SetPoint(411,102));
		
	}
	
	
	return tempToReturn;
}

void gameManager::Draw()
{
	if(gameState == "game")
	{
		vita2d_draw_rectangle(720, 0, 4, 544, RGBA8(255,255,255,255));
		vita2d_draw_rectangle(724, 0, 250, 544, RGBA8(0,0,0,255));
		
		if(waveState == "ready")
		{
			vita2d_font_draw_text(gameFont, 220, 270, RGBA8(255,255,255,255), 32, (char*)"Get Ready");
		}
	
		if(waveState == "game")
		{
			vita2d_font_draw_textf(gameFont, 740, 250, RGBA8(255,255,255,255), 10, "%s" "%d" , (char*)"Score: ", score);
			vita2d_font_draw_textf(gameFont, 740, 270, RGBA8(255,255,255,255), 10, "%s" "%d" , (char*)"Wave: ", wave);
			if(playerObj != NULL)
			{
				vita2d_font_draw_textf(gameFont, 740, 290, RGBA8(255,255,255,255), 10, "%s" "%d" , (char*)"Lives: ", playerObj->lives);
			}
		}		
	}
	
	if(gameState == "gameOver")
	{
		vita2d_draw_rectangle(720, 0, 4, 544, RGBA8(255,255,255,255));
		vita2d_draw_rectangle(724, 0, 250, 544, RGBA8(0,0,0,255));
		
		vita2d_font_draw_text(gameFont, 250, 270, RGBA8(255,255,255,255), 24, (char*)"Game Over");
		vita2d_font_draw_text(gameFont, 115, 320, RGBA8(255,255,255,255), 24, (char*)"Press Start to Restart");
		
		
		vita2d_font_draw_textf(gameFont, 740, 250, RGBA8(255,255,255,255), 10, "%s" "%d" , (char*)"Score: ", score);
			vita2d_font_draw_textf(gameFont, 740, 270, RGBA8(255,255,255,255), 10, "%s" "%d" , (char*)"Wave: ", wave);
			if(playerObj != NULL)
			{
				vita2d_font_draw_textf(gameFont, 740, 290, RGBA8(255,255,255,255), 10, "%s" "%d" , (char*)"Lives: ", playerObj->lives);
			}
	}
	
	
	if(gameState == "thanks")
	{
		vita2d_draw_rectangle(720, 0, 4, 544, RGBA8(255,255,255,255));
		vita2d_draw_rectangle(724, 0, 250, 544, RGBA8(0,0,0,255));
		
		vita2d_font_draw_text(gameFont, 50, 270, RGBA8(255,255,255,255), 24, (char*)"The galaxy has been saved.");
		vita2d_font_draw_text(gameFont, 130, 320, RGBA8(255,255,255,255), 24, (char*)"Thanks for playing!");
		
		
		vita2d_font_draw_textf(gameFont, 740, 250, RGBA8(255,255,255,255), 10, "%s" "%d" , (char*)"Score: ", score);
			vita2d_font_draw_textf(gameFont, 740, 270, RGBA8(255,255,255,255), 10, "%s" "%d" , (char*)"Wave: ", wave);
			if(playerObj != NULL)
			{
				vita2d_font_draw_textf(gameFont, 740, 290, RGBA8(255,255,255,255), 10, "%s" "%d" , (char*)"Lives: ", playerObj->lives);
			}
	}
}

void gameManager::LaunchEnemy()
{
	enemyLaunchTime++;
	if(enemyLaunchTime > 300)
	{
		enemyLaunchTime = 0;
		std::vector<int> listOfAvailableEnemies;
		int enemiesToSendOut = 0;
		if(wave <= 2)
		{
			if(listOfEnemyObj.size() > 1)
			{
				enemiesToSendOut = 1;
			}
			else
			{
				enemiesToSendOut = listOfEnemyObj.size();
			}
			
		}
		else if(wave >= 3 && wave <= 5)
		{
			if(listOfEnemyObj.size() > 3)
			{
				enemiesToSendOut = 3;
			}
			else
			{
				enemiesToSendOut = listOfEnemyObj.size();
			}
			
		}
		else if(wave >= 6 && wave <= 7)
		{
			if(listOfEnemyObj.size() > 5)
			{
				enemiesToSendOut = 5;
			}
			else
			{
				enemiesToSendOut = listOfEnemyObj.size();
			}
		}
		else if(wave >= 8)
		{
			if(listOfEnemyObj.size() > 6)
			{
				enemiesToSendOut = 6;
			}
			else
			{
				enemiesToSendOut = listOfEnemyObj.size();
			}
		}
		
		for(int i = 0; i < listOfEnemyObj.size();i++)
		{
			listOfAvailableEnemies.push_back(i);
		}
		
		for(int i = 0; i < enemiesToSendOut; i++)
		{
			
			int randomNumber = rand() % listOfAvailableEnemies.size();
			listOfEnemyObj[listOfAvailableEnemies[randomNumber]]->Launch();
			listOfEnemyObj[listOfAvailableEnemies[randomNumber]]->waitTime = i * 25;
			listOfAvailableEnemies.erase(listOfAvailableEnemies.begin() + randomNumber);
		}
	}
}

void gameManager::SpawnStars()
{
	for(int y =0; y < 17; y++)
	{
		for(int x = 0; x < 30; x++)
		{
			if(rand() % 3 == 0)
			{
				listOfStarObj.push_back(new stars(rand() % 16 + 8 + (32 * x) , rand() % 16 + 8 + (32 * y),rand() % 90));
			}
		}
	}
	
}

void gameManager::NewGame()
{
	logString = "";
	waveState = "ready";
	nextEnemySpawnTimer = 0;
	enemyWave = 0;
	readyTimer = 0;
	score = 0;
	wave = 0;
	SpawnStars();
	listOfEnemiesInWave.clear();
	doubleRow = false;
	fullGridMove = false;
	hasFiredShot = false;
}

void gameManager::GenerateUFO()
{
	int randomNumber = rand() %2;
	int xPosition = 0;
	if(randomNumber == 0)
	{
		xPosition = -16;
	}
	else
	{
		xPosition = 736;
	}
	
	listOfUfoObj.push_back(new ufo(xPosition,250));
}

void gameManager::Update()
{
	if(gameState == "gameOver")
	{
		if(controllerObj->isStartPressed == true && controllerObj->canStartBePressed == true)
		{
			ClearGame();
			ClearColumnOffset();
			StartNewGame();
			controllerObj->GetCanPresses();
		}
	}
	
	if(gameState == "thanks")
	{
		if(controllerObj->isStartPressed == true && controllerObj->canStartBePressed == true)
		{
			ClearGame();
			ClearColumnOffset();
			MainMenuState();
			controllerObj->GetCanPresses();
		}
	}
	
	if(gameState == "game")
	{
		if(waveState == "ready")
		{
			Ready();
		}
		
		if(waveState == "game")
		{		
			if(score > 10000)
			{
				Bartender_UnlockTrophy(5);
			}
			
			if(score > 20000)
			{
				Bartender_UnlockTrophy(6);
			}
			
			CheckIfWaveIsComplete();
			EnemyMovement();
			if(enemyWave < 6)
			{
				CreateEnemy();
			}
			else
			{
				LaunchEnemy();
			}
			
			if(wave == 2 || wave == 5 || wave == 9)
			{
				if(enemyWave >= 6)
				{
					ufoGeneratorTime++;
				}
				
				if(wave == 2)
				{
					if(ufoGeneratorTime == 1000)
					{
						GenerateUFO();
					}
				}
				
				else if(wave == 5)
				{
					if(ufoGeneratorTime == 1600)
					{
						GenerateUFO();
					}
				}
				else if(wave == 9)
				{
					if(ufoGeneratorTime == 2400)
					{
						GenerateUFO();
					}
				}
			}
		}
		
		if(waveState == "respawn")
		{
			if(allEnemiesInPosition == false)
			{
				return;
			}
			else
			{
				readyTimer++;
			}
		}
	}	
}