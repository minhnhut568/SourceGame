#pragma once
#include "AriseBase.h"
class FloaterBullet :
	public AriseBase
{
public:
	FloaterBullet();
	void onUpdate(float dt) override;
};

