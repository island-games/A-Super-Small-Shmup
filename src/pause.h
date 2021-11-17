#ifndef pause_h_
#define pause_h_

class pause{
public:
	bool isDead;
	int menuNumber;
	
	pause();
	void Draw();
	void Move();
	void Select();
	bool Update();
	
	
};
#endif