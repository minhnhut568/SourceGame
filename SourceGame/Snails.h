#pragma once
#include "Enemy.h"
class Snails :
	public Enemy
{
public:
	Snails();
	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
};

