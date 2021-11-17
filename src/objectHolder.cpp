#include "objectHolder.h"
#include "splashScreen.h"


 std::string gameState = "";
 int score  = 0;
 controllers* controllerObj;
 bool isPaused =  false;
 bool music = true;
 bool soundEffects = true;
 int enemyMoveSpeed;
 std::vector<enemy*> listOfEnemyObj;
 player* playerObj;
 std::vector<playerBullets*> listOfPlayerBulletsObj;
 std::vector<enemyBullets*> listOfEnemyBulletsObj;
 std::vector<splashScreen*> listOfSplashScreenObj;
 std::vector<boss*> listOfBossObj;
 std::vector<mainMenu*> listOfMainMenuObj;
 std::vector<pause*> listOfPauseObj;
std::vector<stars*> listOfStarObj;
std::vector<explosion*> listOfExplosionObj;
std::vector<ufo*> listOfUfoObj;
std::vector<powerUp*> listOfPowerUpObj;
vita2d_texture* spriteTexture = NULL;
 gameManager* gameManagerObj;
 int totalGridOffset = 0;
 std::vector<int> columnOffset;
 
SoLoud::Soloud gSoloud;
SoLoud::Wav playerShotSnd;
SoLoud::Wav playerDeathSnd;
SoLoud::Wav enemyShotSnd;
SoLoud::Wav impactSnd;
SoLoud::Wav powerUpSnd;
SoLoud::Wav bonusSnd; 
SoLoud::Wav musicSnd;
 
int totalGridOffsetDestination = 0;
std::vector<int> columnOffsetDestination;
int totalResetTimer = 0;
int columnResetTimer = 0;
 
 
 
 vita2d_font* logoFont;
 vita2d_font* gameFont;
 vita2d_texture* playerTexture;
 vita2d_texture* mainMenuTexture;
 vita2d_texture* bulletTexture = NULL;
 vita2d_texture* bossTexture = NULL;
 vita2d_texture* pauseTexture;
 vita2d_texture* splashScreenTexture;
 vita2d_texture* enemyExplosionTexture = NULL;
 vita2d_texture* playerExplosionTexture = NULL;
 vita2d_texture* ufoTexture = NULL;
 
 void QuitGame()
 {
	 ClearGame();
	 MainMenuState();
 }
 
 void SplashScreenState()
 {
	 gameState = "splashScreen";
	 listOfSplashScreenObj.push_back(new splashScreen());
 }
 
 void MainMenuState()
 {
	 gameState = "mainMenu";
	 listOfMainMenuObj.push_back(new mainMenu());
 }
 
 void StartNewGame()
 {
	 gameState = "game";
	 
	 playerObj = new player();
	 
	 if(spriteTexture == NULL)
	 {
		 spriteTexture = vita2d_load_PNG_file((char*)"app0:img/sprites.png");
	 }
	 
	 if(bossTexture == NULL)
	 {
		 bossTexture = vita2d_load_PNG_file((char*)"app0:img/boss.png");
	 }
	 
	 if(bulletTexture == NULL)
	 {
		bulletTexture = vita2d_load_PNG_file((char*)"app0:img/bullet.png");
	 }
	 
	 if(playerExplosionTexture == NULL)
	 {
		 playerExplosionTexture = vita2d_load_PNG_file((char*)"app0:img/playerExplosion.png");
	 }
	 
	 if(enemyExplosionTexture == NULL)
	 {
		 enemyExplosionTexture = vita2d_load_PNG_file((char*)"app0:img/enemyExplosion.png");
	 }
	 
	 if(ufoTexture == NULL)
	 {
		 ufoTexture = vita2d_load_PNG_file((char*)"app0:img/ufo.png");
	 }
	 
	 gameManagerObj->NewGame();
 }
 
 void PlaySound(SoLoud::Wav &soundToPlay)
 {
	if(soundEffects == true)
	{
		gSoloud.play(soundToPlay);
	}
 }
 
  void PlayMusic(SoLoud::Wav &musicToPlay)
 {
	if(music == true)
	{
		gSoloud.play(musicToPlay);
	}
 }
 
 void ClearColumnOffset()
 {
	 columnOffset.clear();
	 columnOffset.push_back(0);
	 columnOffset.push_back(0);
	 columnOffset.push_back(0);
	 columnOffset.push_back(0);
	 columnOffset.push_back(0);
	 columnOffset.push_back(0);
	 columnOffset.push_back(0);
	 columnOffset.push_back(0);
	 columnOffset.push_back(0);
	 columnOffset.push_back(0);
	 
	 columnOffsetDestination.clear();
	 columnOffsetDestination.push_back(0);
	 columnOffsetDestination.push_back(0);
	 columnOffsetDestination.push_back(0);
	 columnOffsetDestination.push_back(0);
	 columnOffsetDestination.push_back(0);
	 columnOffsetDestination.push_back(0);
	 columnOffsetDestination.push_back(0);
	 columnOffsetDestination.push_back(0);
	 columnOffsetDestination.push_back(0);
	 columnOffsetDestination.push_back(0);
	 
 }
 
 void ClearGame()
 {
	playerObj = NULL;
	listOfEnemyBulletsObj.clear();
	listOfEnemyObj.clear();
	listOfPlayerBulletsObj.clear();
	listOfBossObj.clear();
	listOfStarObj.clear();
	listOfUfoObj.clear();
	listOfPowerUpObj.clear();
 }