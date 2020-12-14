#pragma once
#include "DelayTime.h"
#include "Enemy.h"

enum SKULLS_STATE {
	SKULLS_STATE_RUN,
	SKULLS_STATE_STAND
};


class Skulls :
	public Enemy
{
public:
	SKULLS_STATE skullsState;
	Skulls();

	DelayTime standDelay;
	DelayTime runDelay;
	bool checkContactPlayer();

	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
};

