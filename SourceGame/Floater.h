#pragma once
#include "Enemy.h"
#include "GameTime.h"
#include "DelayTime.h"


enum FLOATER_ACTION {
	FLOATER_ACTION_FLY,
	FLOATER_ACTION_SHOOT
};

class Floater :
	public Enemy
{
public:

	GameTime shootTime;
	DelayTime shootDelay;

	MovableRect* ground;
	Floater();
	int startY;

	void onUpdate(float dt) override;

	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
};

