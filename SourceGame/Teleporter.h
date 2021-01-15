#pragma once
#include "Enemy.h"
#include "DelayTime.h"
#include "GameTime.h"

enum TELEPORTER_ACTION {
	TELEPORTER_ACTION_WEAR,
	TELEPORTER_ACTION_UNWEAR
};

enum TELEPORTER_STATE {
	TELEPORTER_STATE_STAND,
	TELEPORTER_STATE_MOVE
};

class Teleporter :
	public Enemy
{
	POINT* positions;
	DelayTime standDelay;
	GameTime moveTime;
	TELEPORTER_STATE state;
	int positionIndex;
public:
	Teleporter();
	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
};

