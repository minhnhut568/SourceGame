#pragma once
#include "Enemy.h"
#include "GameTime.h"
#include "DelayTime.h"


class Cannons :
	public Enemy
{
public:
	GameTime shootTime;
	DelayTime shootDelay;
	bool isVertical;

	Cannons();
	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
};

