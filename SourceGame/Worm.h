#pragma once
#include "Enemy.h"

enum WORM_ACTION
{
	WORM_ACTION_RUN,
	WORM_ACTION_CLIMB
};

class Worm :
	public Enemy
{
public:
	Worm();
	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
};