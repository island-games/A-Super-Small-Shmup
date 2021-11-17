#ifndef playerBullets_h_
#define playerBullets_h_

class playerBullets{
	public:
	int x;
	int y;
	int width;
	int height;
	int isDead;
	
	playerBullets(int xPos, int yPos);
	void CheckCollision();
	void Move();
	void Draw();
	bool Update();
};
#endif