#ifndef BOSS_H
#define BOSS_H
#include"raylib.h"
class Boss{
private:
	Rectangle rect;
	int health;
	int direction; 
	
public:
	Boss(float x, float y, float width, float height, int initialHealth);
	void Update(int speed, int screenWidth);
	void Draw()const;
	void TakeDamage();

	int GetHealth() const { 
		return health;
	}
	Rectangle GetRect() const {
		return rect;
	}
};
#endif 