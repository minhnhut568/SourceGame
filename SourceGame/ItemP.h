#pragma once
#include "AriseBase.h"
class ItemP :
	public AriseBase
{
public:
	ItemP();
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;

};

