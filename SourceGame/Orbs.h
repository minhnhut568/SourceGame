#pragma once
#include "Enemy.h"
#include "DelayTime.h"

enum ORBS_STATE
{
	ORBS_STATE_FLY_DOWN,
	ORBS_STATE_FLY_UP,
	ORBS_STATE_FALL
};
class Orbs :
	public Enemy

{
public:
	
	Orbs();
	DelayTime flyDownDelay;
	DelayTime flyUpDelay;

	ORBS_STATE orbsState;
	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
};

