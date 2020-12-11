#pragma once
#include "Enemy.h"

enum FLOATER_STATE {
	FLOATER_STATE_FLY,
	FLOATER_STATE_SHOOT
};

class Floater :
	public Enemy
{
public:

	MovableRect* ground;
	FLOATER_STATE floaterState;
	Floater();
	int startY;
	//int initNx, initNy;

	void onUpdate(float dt) override;

	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
};

