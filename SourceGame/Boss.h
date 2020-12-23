#pragma once
#include "Enemy.h"
class Boss :
	public Enemy
{
public:
	void onUpdate(float dt) override;
};

