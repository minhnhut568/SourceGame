#pragma once
#include "PhysicsObject.h"
#include"SpriteManager.h"
#include"KEY.h"
#include "DelayTime.h"
#include "GameTime.h"
#include "DelayTime.h"

enum PLAYER_OW_ACTION
{
	PLAYER_OW_ACTION_DOWN_STAND,
	PLAYER_OW_ACTION_DOWN_RUN,
	PLAYER_OW_ACTION_UP_RUN,
	PLAYER_OW_ACTION_LEFT_RUN,
	PLAYER_OW_ACTION_UP_STAND,
	PLAYER_OW_ACTION_LEFT_STAND,
	PLAYER_OW_ACTION_DIE
};

enum PLAYER_OW_DIRECTION
{
	PLAYER_OW_DIRECTION_LEFT,
	PLAYER_OW_DIRECTION_RIGHT,
	PLAYER_OW_DIRECTION_UP,
	PLAYER_OW_DIRECTION_DOWN
};

class PlayerOverWorld :
	public PhysicsObject
{
	int health = 8;
	int moveX, moveY;
	static PlayerOverWorld* instance;
	PLAYER_OW_DIRECTION playerDirection;

	DelayTime shootDelay;
public:

	static PlayerOverWorld* getInstance();
	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
	GameTime blinkTime;
	DelayTime blinkDelay;
	DelayTime blinkCantControlDelay;
	void onAABBCheck(MovableRect* other) override;
	void setPlayerDirection(PLAYER_OW_DIRECTION direction);

	PlayerOverWorld();
	~PlayerOverWorld();

};