#pragma once
#include "PhysicsObject.h"
#include"DelayTime.h"
enum PLAYER_MINI_ACTION 
{
	PLAYER_MINI_ACTION_STAND,
	PLAYER_MINI_ACTION_RUN,
	PLAYER_MINI_ACTION_JUMP,
	PLAYER_MINI_ACTION_DIVE,
	PLAYER_MINI_ACTION_CLIMB,
	PLAYER_MINI_ACTION_DYING,
	PLAYER_MINI_ACTION_DIE
};

enum PLAYER_MINI_STATE
{
	PLAYER_MINI_STATE_NORMAL,
	PLAYER_MINI_STATE_ON_LADDER
};

class PlayerMini :
	public PhysicsObject
{
public:
	MovableRect* ladder;
	PLAYER_MINI_STATE playerMiniState;
	DelayTime bulletDelay;
	PlayerMini();

	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;

	GameTime blinkTime;
	DelayTime blinkDelay;
	DelayTime blinkCantControlDelay;
	void onAABBCheck(MovableRect* other) override;
};

