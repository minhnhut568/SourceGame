#pragma once
#include "AriseBase.h"

enum BULLET_ANIMATION
{
	BULLET_ANIMATION_HOR,
	BULLET_ANIMATION_VER
};

class PlayerBullet :
	public AriseBase
{
public:
	void onUpdate(float dt);
	void onAABBCheck(MovableRect* other) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;

	PlayerBullet();
};

