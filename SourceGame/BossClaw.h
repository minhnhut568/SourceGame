#pragma once
#include "AriseBase.h"
class BossClaw :
	public AriseBase
{
public:
	BaseObject* boss;
	int relativeX, relativeY;
	BossClaw();
	void onUpdate(float dt) override;
	void render() override;
	void onAABBCheck(MovableRect* other) override;
};

