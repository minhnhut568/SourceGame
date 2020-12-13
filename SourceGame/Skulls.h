#pragma once
#include "Enemy.h"
#include "DelayTime.h"
#include "GameTime.h"

enum SKULLS_ACTION {
	SKULLS_ACTION_FLY,
	SKULLS_ACTION_RELEASE
};
class Skulls :
	public Enemy
{
public:

	GameTime shootTime;
	DelayTime shootDelay;

	MovableRect* ground;
	Skulls();
	int startY;

	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
};

