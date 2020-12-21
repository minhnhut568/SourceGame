#pragma once
#include "Enemy.h"
class Cannons :
	public Enemy
{
public:
	Cannons();
	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
};

