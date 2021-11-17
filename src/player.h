#ifndef player_h_
#define player_h_

class player{
	public:
	
	bool isDead;
	int x;
	int y;
	int width;
	int height;
	int lives;
	int activeBullets;
	int health;
	int respawnWaitTime;
	int invincibleTime;
	bool hasPowerUp;
	
	player();
	void Respawn();
	void Shoot();
	void Move();
	void GameOver();
	void CheckCollision();
	void CheckDeath();
	void PauseGame();
	void Draw();
	bool Update();
	
};
#endif