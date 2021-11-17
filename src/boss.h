#ifndef boss_h_
#define boss_h_

#include <string>

class boss{
public:
	
	int x;
	int y;
	int moveSpeed;
	int selectedAttackPattern;
	int attackWaitTime;
	int attackTime;
	int attackTimeLimit;
	int animationTime;
	int health;
	int dieTime;
	int waitToMoveTime;
	bool isDead;
	std::string characterState;
	std::string direction;
	
	boss();
	void Draw();
	void DecideAction();
	void Enter();
	void Move();
	void Shoot(int xSpeed, int ySpeed);
	void Attack();
	void Wait();
	void Die();
	void CheckDeath();
	bool Update();
	
};
#endif