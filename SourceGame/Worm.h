#pragma once
#include "Enemy.h"

enum WORM_ACTION
{
	WORM_ACTION_RUN,
	WORM_ACTION_CLIMB
};

enum WORM_STATE
{
	WORM_STATE_RUN,
	WORM_STATE_JUMP
};

class Worm :
	public Enemy
{
	WORM_STATE wormState;
	int startY;
public:
	Worm();
	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
};