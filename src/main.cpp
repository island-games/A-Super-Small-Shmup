#include <bartender.h>
#include <vita2d.h>
#include "objectHolder.h"
#include "controllers.h"
#include "gameManager.h"


void Draw()
{
	vita2d_start_drawing();
	vita2d_clear_screen();
	for(int i = listOfSplashScreenObj.size() -1; i >= 0; i--)
	{
		listOfSplashScreenObj[i]->Draw();
	}
	
	for(int i = listOfMainMenuObj.size() -1; i >= 0; i--)
	{
		listOfMainMenuObj[i]->Draw();
	}
	
	for(int i = listOfStarObj.size() -1; i >= 0; i--)
	{
		listOfStarObj[i]->Draw();
	}
	for(int i = listOfEnemyObj.size()-1; i >=0; i--)
	{
		listOfEnemyObj[i]->Draw();
	}
	
	for(int i = listOfEnemyBulletsObj.size()-1; i >=0; i--)
	{
		listOfEnemyBulletsObj[i]->Draw();
	}
	
	for(int i = listOfBossObj.size()-1; i >=0; i--)
	{
		listOfBossObj[i]->Draw();
	}
	
	for(int i = listOfPlayerBulletsObj.size() -1; i >= 0; i--)
	{
		listOfPlayerBulletsObj[i]->Draw();
	}
	
	for(int i = listOfExplosionObj.size() -1; i >= 0; i--)
	{
		listOfExplosionObj[i]->Draw();
	}
	
	for(int i = listOfPowerUpObj.size() -1; i >= 0; i--)
	{
		listOfPowerUpObj[i]->Draw();
	}
	
	for(int i = listOfUfoObj.size() -1; i >= 0; i--)
	{
		listOfUfoObj[i]->Draw();
	}
	
	if(playerObj != NULL)
	{
		playerObj->Draw();
	}
	
	if(gameManagerObj != NULL)
	{
		gameManagerObj->Draw();
	}
	
	for(int i = listOfPauseObj.size() -1; i >= 0; i--)
	{
		listOfPauseObj[i]->Draw();
	}
	
	vita2d_end_drawing();		
	vita2d_swap_buffers();
}

void Update()
{
	while(true)
	{
		controllerObj->CheckInputs();
		if(isPaused == false)
		{
			for(int i = listOfSplashScreenObj.size()-1; i >= 0; i--)
			{
				bool isDead = listOfSplashScreenObj[i]->Update();
				
				if(isDead == true)
				{
					listOfSplashScreenObj.erase(listOfSplashScreenObj.begin() + i);
				}
			}
			
			for(int i = listOfMainMenuObj.size()-1; i >= 0; i--)
			{
				bool isDead = listOfMainMenuObj[i]->Update();
				
				if(isDead == true)
				{
					listOfMainMenuObj.erase(listOfMainMenuObj.begin() + i);
				}
			}
			
			if(gameManagerObj != NULL)
			{
				gameManagerObj->Update();				
			}
			
			for(int i = listOfEnemyObj.size()-1; i >= 0; i--)
			{
				bool isDead = listOfEnemyObj[i]->Update();
				
				if(isDead == true)
				{
					listOfEnemyObj.erase(listOfEnemyObj.begin() + i);
				}
			}
			
			for(int i = listOfPowerUpObj.size() - 1; i >= 0; i--)
			{
				bool isDead = listOfPowerUpObj[i]->Update();
				
				if(isDead == true)
				{
					listOfPowerUpObj.erase(listOfPowerUpObj.begin() + i);
				}
			}
			
			for(int i = listOfUfoObj.size() - 1; i >= 0; i--)
			{
				bool isDead = listOfUfoObj[i]->Update();
				
				if(isDead == true)
				{
					listOfUfoObj.erase(listOfUfoObj.begin() + i);
				}
			}
			
			if(playerObj != NULL)
			{
				bool isDead = playerObj->Update();
				
				if(isDead == true)
				{
					playerObj = NULL;
				}
			}
			
			for(int i = listOfBossObj.size() - 1; i >= 0; i--)
			{
				bool isDead = listOfBossObj[i]->Update();
				
				if(isDead == true)
				{
					listOfBossObj.erase(listOfBossObj.begin() + i);
				}
			}
			
			
			
			for(int i = listOfPlayerBulletsObj.size()-1; i >= 0; i--)
			{
				bool isDead = listOfPlayerBulletsObj[i]->Update();
				
				if(isDead == true)
				{
					listOfPlayerBulletsObj.erase(listOfPlayerBulletsObj.begin() + i);
				}
			}
			
			
			
			for(int i = listOfEnemyBulletsObj.size()-1; i >= 0; i--)
			{
				bool isDead = listOfEnemyBulletsObj[i]->Update();
				
				if(isDead == true)
				{
					listOfEnemyBulletsObj.erase(listOfEnemyBulletsObj.begin() + i);
				}
			}
			
			for(int i = listOfStarObj.size()-1; i >= 0; i--)
			{
				bool isDead = listOfStarObj[i]->Update();
				
				if(isDead == true)
				{
					listOfStarObj.erase(listOfStarObj.begin() + i);
				}
			}
			
			for(int i = listOfExplosionObj.size()-1; i >= 0; i--)
			{
				bool isDead = listOfExplosionObj[i]->Update();
				
				if(isDead == true)
				{
					 listOfExplosionObj.erase(listOfExplosionObj.begin() + i);
				}
			}
			
		}
		
		else
		{
			for(int i = listOfPauseObj.size()-1; i >= 0; i--)
			{
				bool isDead = listOfPauseObj[i]->Update();
				
				if(isDead == true)
				{
					listOfPauseObj.erase(listOfPauseObj.begin() + i);
				}
			}
		}
		
		controllerObj->GetCanPresses();
		Draw();
	}
}

int main()
{
	vita2d_init();
	vita2d_set_clear_color(RGBA8(0,0,0,255));
    Bartender_StartBartender((char*)"password",(char*)"ISLD00000");
	int timeCounter = 0;             
	logoFont = vita2d_load_font_file("app0:img/ka1.ttf");
	gameFont = vita2d_load_font_file("app0:img/ARCADE_N.ttf");
	controllerObj = new controllers(0);
	gameManagerObj = new gameManager();
	SplashScreenState();
	ClearColumnOffset();
	
	gSoloud.init();
	playerShotSnd.load("app0:snd/playerLaser.wav");
	playerDeathSnd.load("app0:snd/playerDeath.wav");
	enemyShotSnd.load("app0:snd/enemyLaser.wav");;
	impactSnd.load("app0:snd/enemyImpact.wav");;
	powerUpSnd.load("app0:snd/powerUp.wav");;
	bonusSnd.load("app0:snd/bonus.wav");
	musicSnd.load("app0:snd/music.wav");
	musicSnd.setLooping(1);
	
	Update();

}