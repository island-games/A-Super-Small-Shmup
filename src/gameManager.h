#ifndef gameManager_h_
#define gameManager_h_
#include <string>
#include <vector>
#include "Vector2.h"

class gameManager{
	public:
		
	struct preenemy
	{
		int xPos;
		int yPos;
		int enemyType;
		bool shootWhileEntering;
				
	};
	std::string logString;
	std::string waveState;
	int wave;
	int enemyWave;
	int x;
	int y;
	int enemyLaunchTime;
	int readyTimer;
	int nextEnemySpawnTimer;
	int bonusScore;
	int ufoGeneratorTime;
	bool doubleRow;
	bool fullGridMove;
	bool allEnemiesInPosition;
	bool canGetBonus;
	bool hasFiredShot;
	std::vector<preenemy> listOfEnemiesInWave;
	std::vector<Vector2> pathToFollow;
	std::vector<Vector2> pathToFollow2;
	
	gameManager();
	void NewGame();
	void EnemyMovement();
	void AddBonus();
	void Ready();
	void SpawnStars();
	void RespawnPlayer();
	void CreateEnemy();
	void LaunchEnemy();
	void GenerateUFO();
	preenemy CreatePreenemy(int tempX, int tempY, int typeTemp);
	preenemy CreatePreenemy(int tempX, int tempY, int typeTemp, bool tempShootWhileEntering);
	void SetPatternForWave();
	void CheckIfWaveIsComplete();
	bool CheckInPosition();
	std::vector<Vector2> GetTravelPath(int selectedPath);
	std::vector<Vector2> GetTravelPath2(int selectedPath);
	Vector2 SetPoint(int tempX, int tempY);
	void Draw();
	void Update();
};
#endif