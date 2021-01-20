#pragma once
#include "Enemy.h"
#include "AriseBase.h"

class Mines :
	public Enemy
{
public:

	bool isVertical;

	Mines();
	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
};