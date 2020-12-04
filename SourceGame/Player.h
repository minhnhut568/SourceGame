#pragma once
#include "PhysicsObject.h"
#include"SpriteManager.h"
#include"KEY.h"
#include "DelayTime.h"

enum PLAYER_ACTION
{
	PLAYER_ACTION_STAND,
	PLAYER_ACTION_RUN,
	PLAYER_ACTION_JUMP,
	PLAYER_ACTION_JUMP_DOWN,
	PLAYER_ACTION_SHOOTING_UP,
	PLAYER_ACTION_SHOOT_UP,
	PLAYER_ACTION_SHOOTING_DOWN
};

class Player :
	public PhysicsObject
{
	static PhysicsObject* playerMain;
	static PhysicsObject* playerMini;
public:
	static PhysicsObject* getPlayerMain();
	static PhysicsObject* getPlayerMini();

	static PhysicsObject* instance;
	DelayTime bulletDelay;

	static PhysicsObject* currentPlayer;

	static void changeToPlayerMini();
	static void changeToPlayerMain();

	static PhysicsObject* getInstance();
	void onUpdate(float dt) override;
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;

	static void updatePlayer(float dt);
	static void renderPlayer();

	Player();
	~Player();
};