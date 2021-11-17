#ifndef powerUp_h
#define powerUp_h

class powerUp{
public:
	int x;
	int y;
	int width;
	int height;
	bool isDead;
	
	powerUp(int tempX, int tempy);
	void Draw();
	bool Update();
};
#endif