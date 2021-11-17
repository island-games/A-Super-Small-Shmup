#ifndef enemy_h_
#define enemy_h_

#include <string>
#include <vector>
#include "Vector2.h"

class enemy{
public:
int x;
int y;
int waitTime;
std::string xDirection;
std::string yDirection;
int enemyGridPositionX;
int enemyGridPositionY;
int enemyType;
int width;
int height; 
int health;
std::string direction;
bool inPosition;
bool isDead;
bool shootWhileEntering;
std::vector<Vector2> points;
std::vector<int> shootTime;

float angle;
float RAD;

enemy(int xPos, int yPos, int tempType, int enemyGridPositionTempx, int enemyGridPositionTempy, std::vector<Vector2> listOfPoints, bool tempShootWhileEntering);
void Shoot();
void Launch();
void RemovePoint();
void Move();
void Rotate();
void ResetY();
void CheckHealth();
void SetHomePosition();
void Draw();
bool Update();

};
#endif