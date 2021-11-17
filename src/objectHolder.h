#ifndef objectHolder_h_
#define objectHolder_h_

#include <vector>
#include <string>
#include <string.h>
#include <vita2d.h>
#include <soloud.h>
#include <soloud_wav.h>
#include <bartender.h>

#include "controllers.h"
#include "enemy.h"
#include "enemyBullets.h"
#include "player.h"
#include "playerBullets.h"
#include "splashScreen.h"
#include "boss.h"
#include "mainMenu.h"
#include "pause.h"
#include "gameManager.h"
#include "stars.h"
#include "explosion.h"
#include "ufo.h"
#include "powerUp.h"


	
extern bool isPaused;
extern bool music;
extern bool soundEffects;
extern int enemyMoveSpeed;
extern std::vector<enemy*> listOfEnemyObj;
extern  player* playerObj;
extern std::vector<playerBullets*> listOfPlayerBulletsObj;
extern std::vector<enemyBullets*> listOfEnemyBulletsObj;
extern std::vector<splashScreen*> listOfSplashScreenObj; 
extern std::vector<boss*> listOfBossObj;
extern std::vector<mainMenu*> listOfMainMenuObj; 
extern std::vector<pause*> listOfPauseObj; 
extern std::vector<stars*> listOfStarObj;
extern std::vector<explosion*> listOfExplosionObj;
extern std::vector<ufo*> listOfUfoObj;
extern std::vector<powerUp*> listOfPowerUpObj;
extern std::string gameState;
extern controllers* controllerObj;
extern gameManager* gameManagerObj; 
extern int totalGridOffset;
extern int totalGridOffsetDestination;
extern std::vector<int> columnOffset;
extern std::vector<int> columnOffsetDestination;
extern int totalResetTimer;
extern int columnResetTimer;
extern int score;
extern SoLoud::Soloud gSoloud;
extern SoLoud::Wav playerShotSnd;
extern SoLoud::Wav playerDeathSnd;
extern SoLoud::Wav enemyShotSnd;
extern SoLoud::Wav impactSnd;
extern SoLoud::Wav powerUpSnd;
extern SoLoud::Wav bonusSnd;

extern SoLoud::Wav musicSnd;


extern vita2d_font* logoFont;
extern vita2d_font* gameFont;
extern vita2d_texture* bulletTexture;
extern vita2d_texture* spriteTexture;
extern vita2d_texture* mainMenuTexture;
extern vita2d_texture* bossTexture;
extern vita2d_texture* pauseTexture;
extern vita2d_texture* splashScreenTexture;
extern vita2d_texture* enemyExplosionTexture;
extern vita2d_texture* playerExplosionTexture;
extern vita2d_texture* ufoTexture;

extern void SplashScreenState();
extern void MainMenuState();
extern void StartNewGame();
extern void QuitGame();
extern void ClearGame();
extern void ClearColumnOffset();
extern void PlaySound(SoLoud::Wav &soundToPlay);
extern void PlayMusic(SoLoud::Wav &musicToPlay);

#endif