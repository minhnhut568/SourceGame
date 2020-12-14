#pragma once
#include "AriseBase.h"
#include "DelayTime.h"
class SkullsBullet :
	public AriseBase
{
public:
	DelayTime liveDelay;
	SkullsBullet();
	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
};

