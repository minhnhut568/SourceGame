#pragma once
#include "Enemy.h"
#include "DelayTime.h"
#include "GameTime.h"
#include "PlayerOverWorld.h"

enum EYEBALLS_STATE {
	EYEBALLS_STATE_STAND,
	EYEBALLS_STATE_MOVE
};

class Eyeballs :
	public Enemy
{
	POINT* positions;
	DelayTime standDelay;
	DelayTime runDelay;

	GameTime shootTime;
	GameTime moveTime;
	int positionIndex;
public:
	EYEBALLS_STATE eyeballsState;
	Eyeballs();

	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
};