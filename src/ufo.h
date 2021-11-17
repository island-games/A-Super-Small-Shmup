#ifndef ufo_h
#define ufo_h

class ufo{
public:
	
	int x;
	int y;
	int width;
	int height;
	int health;
	bool isDead;
	std::string direction;
	
	ufo(int tempX, int tempy);
	void Move();
	void CheckLife();
	void Draw();
	bool Update();
	
};
#endif