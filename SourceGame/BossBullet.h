#pragma once
#include "AriseBase.h"

class BossBullet :
	public AriseBase
{
public:

	void onUpdate(float dt);
	void onAABBCheck(MovableRect* other) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;

	BossBullet();
};

