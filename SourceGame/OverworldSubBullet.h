#pragma once
#include "AriseBase.h"
#include "DelayTime.h"

enum PLAYERMINI_BULLET_ANIMATION {
	PLAYERMINI_BULLET_ANIMATION_SHOOTING,
	PLAYERMINI_BULLET_ANIMATION_BEFORE_EXPLOSION,
	PLAYERMINI_BULLET_ANIMATION_EXPLOSION
};

enum PLAYERMINI_BULLET_STATE {
	PLAYERMINI_BULLET_STATE_SHOOTING,
	PLAYERMINI_BULLET_STATE_BEFORE_EXPLOSION,
	PLAYERMINI_BULLET_STATE_EXPLOSION
};
class OverworldSubBullet :
	public AriseBase
{
	DelayTime shootingDelay;
	DelayTime beforeExplosionDelay;
	DelayTime explosingDelay;
	PLAYERMINI_BULLET_STATE state;
public:
	void onUpdate(float dt);
	void onAABBCheck(MovableRect* other) override;
	OverworldSubBullet();
};

