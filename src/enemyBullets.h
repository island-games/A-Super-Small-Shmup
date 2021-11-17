#ifndef enemyBullets_h_
#define enemyBullets_h_
class enemyBullets{
public:

int x;
int y;
int width;
int height;
int moveSpeed;
int xSpeed;
bool isDead;

enemyBullets(int xPos, int yPos);
enemyBullets(int xPos, int yPos, int xSpeedTemp, int ySpeedTemp);
void Draw();
void Move();
bool Update();

};
#endif