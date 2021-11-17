#include "pause.h"
#include "objectHolder.h"

pause::pause()
{
	isDead = false;
	menuNumber = 0;
}

void pause::Draw()
{
	vita2d_draw_rectangle(280, 72, 400, 400, RGBA8(255,255,255,255));
	vita2d_draw_rectangle(284, 76, 392, 392, RGBA8(0,0,0,255));
	vita2d_font_draw_text(logoFont, 309, 135, RGBA8(255,255,255,255), 64, (char*)"Paused");
	
	std::string musicState = "yes";
	std::string soundState = "yes";
	
	if(music == true)
	{
		musicState = "ON";
	}
	else
	{
		musicState = "OFF";
	}
	
	if(soundEffects == true)
	{
		soundState = "ON";
	}
	else
	{
		soundState = "OFF";
	}
	
	switch(menuNumber)
	{
		case 0:
			vita2d_font_draw_text(gameFont, 335, 200, RGBA8(255,0,0,255), 32, (char*)"Contine");
			vita2d_font_draw_textf(gameFont, 335, 250, RGBA8(255,255,255,255), 32, "%s" "%s",(char*)"Sound: ",(char*)soundState.c_str());
			vita2d_font_draw_textf(gameFont, 335, 300, RGBA8(255,255,255,255), 32, "%s" "%s",(char*)"Music: ",musicState.c_str());
			vita2d_font_draw_text(gameFont, 335, 350, RGBA8(255,255,255,255), 32, (char*)"Quit Game");
			break;
			
		case 1:
			vita2d_font_draw_text(gameFont, 335, 200, RGBA8(255,255,255,255), 32, (char*)"Contine");
			vita2d_font_draw_textf(gameFont, 335, 250, RGBA8(255,0,0,255), 32, "%s" "%s",(char*)"Sound: ",(char*)soundState.c_str());
			vita2d_font_draw_textf(gameFont, 335, 300, RGBA8(255,255,255,255), 32,"%s" "%s", (char*)"Music: ",(char*)musicState.c_str());
			vita2d_font_draw_text(gameFont, 335, 350, RGBA8(255,255,255,255), 32, (char*)"Quit Game");
			
			break;
			
		case 2:
			vita2d_font_draw_text(gameFont, 335, 200, RGBA8(255,255,255,255), 32, (char*)"Contine");
			vita2d_font_draw_textf(gameFont, 335, 250, RGBA8(255,255,255,255), 32, "%s""%s",(char*)"Sound: ",(char*)soundState.c_str());
			vita2d_font_draw_textf(gameFont, 335, 300, RGBA8(255,0,0,255), 32, "%s""%s",(char*)"Music: ",(char*)musicState.c_str());
			vita2d_font_draw_text(gameFont, 335, 350, RGBA8(255,255,255,255), 32, (char*)"Quit Game");
			break;
			
		case 3:
			vita2d_font_draw_text(gameFont, 335, 200, RGBA8(255,255,255,255), 32, (char*)"Contine");
			vita2d_font_draw_textf(gameFont, 335, 250, RGBA8(255,255,255,255), 32, "%s""%s",(char*)"Sound: ",(char*)soundState.c_str());
			vita2d_font_draw_textf(gameFont, 335, 300, RGBA8(255,255,255,255), 32, "%s""%s",(char*)"Music: ",(char*)musicState.c_str());
			vita2d_font_draw_text(gameFont, 335, 350, RGBA8(255,0,0,255), 32, (char*)"Quit Game");
			break;

	}
}

void pause::Move()
{
	
	if(controllerObj->isUpPressed == true && controllerObj->canUpBePressed == true)
	{
		menuNumber--;
		if(menuNumber < 0)
		{
			menuNumber = 3;
		}
	}
	
	if(controllerObj->isDownPressed == true && controllerObj-> canDownBePressed == true)
	{
		menuNumber++;
		if(menuNumber > 3)
		{
			menuNumber = 0;
		}
	}
}

void pause::Select()
{
	//Contine
	//Sound Effects
	//Music
	//Quit
	if(controllerObj->isStartPressed == true && controllerObj->canStartBePressed == true)
	{
		isDead = true;
		controllerObj->GetCanPresses();
	}
	
	if(controllerObj->isCrossPressed == true && controllerObj->canCrossBePressed == true)
	{
		controllerObj->GetCanPresses();
		switch(menuNumber)
		{
			case 0:
				isDead = true;
				break;
			
			case 1:
				if(soundEffects == true)
				{
					soundEffects = false;
				}
				else
				{
					soundEffects = true;
				}
				break;
				
			case 2:
				if(music == true)
				{
					music = false;
				}
				else
				{
					music = true;
				}
				break;
				
			case 3:
				QuitGame();
				isDead = true;
				break;
				
		}
	}
}

bool pause::Update()
{
	Move();
	Select();
	
	if(isDead == true)
	{
		isPaused = false;
	}
	return isDead;
}