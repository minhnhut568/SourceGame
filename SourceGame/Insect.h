#pragma once
#include "Enemy.h"
#include "DelayTime.h"

enum INSECT_STATE
{
	INSECT_STATE_FLY_DOWN,
	INSECT_STATE_FLY_UP,
	INSECT_STATE_FALL
};
class Insect :
	public Enemy
{
public:
	Insect();
	DelayTime flyDownDelay;
	DelayTime flyUpDelay;

	INSECT_STATE insectState;

	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
};

