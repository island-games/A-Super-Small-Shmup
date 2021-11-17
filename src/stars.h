#ifndef stars_h_
#define stars_h_
class stars{
public:
	int x;
	int y;
	int time;
	bool isDead;
	
	
	stars(int tempX, int tempY, int tempTime);
	void Draw();
	bool Update();
};
#endif