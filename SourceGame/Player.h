﻿#pragma once
#include "PhysicsObject.h"
#include"SpriteManager.h"
#include"KEY.h"
#include "DelayTime.h"

enum PLAYER_ACTION
{
	/* animation đầu tiên */
	PLAYER_ACTION_STAND,
	/* animation thứ 2 */
	PLAYER_ACTION_RUN,
	/* animation thứ 3 */
	PLAYER_ACTION_JUMP,
};

class Player :
	public PhysicsObject
{
	static Player* instance;
	DelayTime bulletDelay;

public:
	static Player* getInstance();
	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
	Player();
	~Player();
};

