#pragma once
#include "PhysicsObject.h"
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
class PlayerMini :
	public PhysicsObject
{
public:
	PlayerMini();

	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
};

