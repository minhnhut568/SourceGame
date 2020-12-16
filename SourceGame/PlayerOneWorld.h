#pragma once
#include "PhysicsObject.h"
#include"SpriteManager.h"
#include"KEY.h"
#include "DelayTime.h"

enum PLAYER_OW_ACTION
{
	PLAYER_OW_ACTION_DOWN_STAND,
	PLAYER_OW_ACTION_DOWN_RUN,
	PLAYER_OW_ACTION_UP_RUN,
	PLAYER_OW_ACTION_LEFT_RUN,
	PLAYER_OW_ACTION_UP_STAND,
	PLAYER_OW_ACTION_LEFT_STAND
};

enum PLAYER_OW_DIRECTION
{
	PLAYER_OW_DIRECTION_LEFT,
	PLAYER_OW_DIRECTION_RIGHT,
	PLAYER_OW_DIRECTION_UP,
	PLAYER_OW_DIRECTION_DOWN
};

class PlayerOneWorld :
	public PhysicsObject
{
	int moveX, moveY;
	static PlayerOneWorld* instance;
public:
	static PlayerOneWorld* getInstance();
	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
	void onAABBCheck(MovableRect* other) override;
	void setPlayerDirection(PLAYER_OW_DIRECTION direction);
	PlayerOneWorld();
	~PlayerOneWorld();

};