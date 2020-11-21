#pragma once
#include "BaseObject.h"
#include "World.h"
class Gate :
	public BaseObject
{
public:
	World* world;
	void onAABBCheck(MovableRect* other) override;
};

