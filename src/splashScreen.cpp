#include "splashScreen.h"
#include "objectHolder.h"

splashScreen::splashScreen()
{
	isDead = false;
	timer = 0;
	if(splashScreenTexture == NULL)
	{
		splashScreenTexture = vita2d_load_PNG_file((char*)"app0:img/splashScreen.png");
	}
}

void splashScreen::Draw()
{
	vita2d_draw_rectangle(0, 0, 960, 544, RGBA8(255,255,255,255));
	vita2d_draw_texture(splashScreenTexture, 380, 172);
}

bool splashScreen::Update()
{
	timer++;
	
	if(controllerObj->isStartPressed == true && controllerObj->canStartBePressed == true ||
		controllerObj->isCrossPressed == true && controllerObj->canCrossBePressed == true)
	{
		if(timer > 30)
		{
			timer = 301;
		}
	}
	
	if(timer > 300)
	{
		isDead = true;
		MainMenuState();
	}
	
	return isDead;
}