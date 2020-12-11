#include "Gunner.h"

Gunner::Gunner()
{
	walkDelay.init(S("gunner_walk_delay"));
	jumpDelay.init(S("gunner_jump_delay"));

	walkDelay.start();
	setDirection(-1);
}

void Gunner::onUpdate(float dt)
{
	walkDelay.update();
	jumpDelay.update();
	setVx(getDirection() * S("gunner_vx"));

	if (walkDelay.isTerminated())
	{
		jumpDelay.start();
	}

	if (jumpDelay.isOnTime())
	{
		if (getIsOnGround())
		{
			setVy(S("gunner_vy"));
		}
	}

	if (jumpDelay.isTerminated())
	{
		walkDelay.start();
	}
	Enemy::onUpdate(dt);
}

void Gunner::onCollision(MovableRect* other, float collisionTime, int nx, int ny)
{
	if (nx != 0 && other->getCollisionType() == COLLISION_TYPE_GROUND)
	{
		setDirection(nx);
	}
	Enemy::onCollision(other, collisionTime, nx, ny);
}
