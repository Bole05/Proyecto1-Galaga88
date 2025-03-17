#infdef PLAYER_H
#define PLAYER_H
#include "raylib.h"
class Player {
private:
	Rectangle rect;
	int lives;
	const int SPEED = 5;
public:
	Player(float x, float y, float width, float height, int initialLives);
	void Update();
	void Draw();
	void TakeDaamge();
	float GetX()const {
		return rect.x;
	}
	float Gety()const {
		return rect.y;
	}
	Rectangle GetRect() const {
		return rect;
	}
	int Getlives()const {
		return lives;
	}
};

#endif // PLAYER_H
