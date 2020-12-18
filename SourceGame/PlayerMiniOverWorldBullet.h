#pragma once
#include "AriseBase.h"
class PlayerMiniOverWorldBullet :
	public AriseBase
{
public:
	void onUpdate(float dt);
	void onAABBCheck(MovableRect* other) override;
	PlayerMiniOverWorldBullet();
};

