#include "mainMenu.h"
#include "objectHolder.h"

mainMenu::mainMenu()
{
	isDead = false;
	timer = 0;
	PlayMusic(musicSnd);
	
}

void mainMenu::Draw()
{
	vita2d_font_draw_text(logoFont, 150, 80, RGBA8(255,255,255,255), 64, (char*)"A Super Small");
	vita2d_font_draw_text(logoFont, 330, 180, RGBA8(255,255,255,255), 64, (char*)"SHMUP");
	
	if(timer <= 45)
	{
		vita2d_font_draw_text(gameFont, 315, 450, RGBA8(255,255,255,255), 32, (char*)"Press Start");
	}
}

bool mainMenu::Update()
{
	timer++;
	if(timer >= 60)
	{
		timer = 0;
	}
	if(controllerObj->isStartPressed == true && controllerObj->canStartBePressed == true)
	{
		isDead = true;
		musicSnd.stop();
		StartNewGame();
		controllerObj->GetCanPresses();
	}
	
	return isDead;
}