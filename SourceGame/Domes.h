#pragma once
#include "Enemy.h"

enum DOMES_STATE
{
	DOMES_STATE_RUN,
	DOMES_STATE_WAIT,
	DOMES_STATE_FIRE
};

enum DOMES_ANIMTION
{
	DOMES_UP,
	DOMES_LEFT,
	DOMES_RIGHT,
	DOMES_DOWN
};

class Domes :
	public Enemy
{
public:

	MovableRect* ground;

	Domes();
	DOMES_STATE domesState;
	int moveX, moveY;

	int initNx, initNy;

	void onUpdate(float dt) override;

	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;

};

