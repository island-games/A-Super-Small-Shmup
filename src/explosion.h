#ifndef explosion_h
#define explosion_h
class explosion
{
public:
		int x;
		int y;
		int explosionTime;
		int explosionType;
		bool isDead;
		
		
		explosion(int tempX, int tempY, int tempExplosionType);
		void Draw();
		bool Update();

};
#endif