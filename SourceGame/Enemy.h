#pragma once
#include "PhysicsObject.h"
class Enemy :
	public PhysicsObject
{
public:
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
	void setDirectionFollowPlayer();
	void onUpdate(float dt) override;

	void setConflicBullet() override;
};

