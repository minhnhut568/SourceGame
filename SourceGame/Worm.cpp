#include "Worm.h"

Worm::Worm()
{
	setAnimation(WORM_ACTION::WORM_ACTION_RUN);
}

void Worm::onUpdate(float dt)
{
	setDirectionFollowPlayer();
	setVx(S("worm_dx") * getDirection());

	if (getIsOnGround())
	{
		setPhysicsEnable(false);
	}

	Enemy::onUpdate(dt);
}

void Worm::onCollision(MovableRect* other, float collisionTime, int nx, int ny)
{
	if (nx != 0)
	{
		setDy(S("worm_dy"));
		setAnimation(WORM_ACTION::WORM_ACTION_CLIMB);
	}
	Enemy::onCollision(other, collisionTime, nx, ny);
}
