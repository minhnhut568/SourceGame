#pragma once
#include "Enemy.h"
#include"DelayTime.h"
enum GUNNER_STATE {
	GUNNER_STATE_WALK,
	GUNNER_STATE_JUMP
};
class Gunner :
	public Enemy
{
public:
	DelayTime walkDelay, jumpDelay;
	GUNNER_STATE gunnerState;
	Gunner();
	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
};

