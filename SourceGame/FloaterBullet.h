#pragma once
#include "AriseBase.h"
class FloaterBullet :
	public AriseBase
{
public:
	FloaterBullet();
	void onAABBCheck(MovableRect* other) override;
	void onUpdate(float dt) override;
};

