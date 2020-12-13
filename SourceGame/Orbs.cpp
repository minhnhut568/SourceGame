#include "Orbs.h"

Orbs::Orbs()
{
	flyDownDelay.init(S("insect_flyDownDelay"));
	flyUpDelay.init(S("insect_flyUpDelay"));
	orbsState = ORBS_STATE_FLY_DOWN;
	flyDownDelay.start();
	setDirection(-1);
}

void Orbs::onUpdate(float dt)
{
	flyDownDelay.update();
	flyUpDelay.update();
	switch (orbsState)
	{
	case ORBS_STATE_FLY_DOWN:
		setDx(getDirection());
		setDy(-1);
		if (flyDownDelay.isTerminated() || getIsOnGround())
		{
			orbsState = ORBS_STATE_FLY_UP;
			flyUpDelay.start();
		}
		break;
	case ORBS_STATE_FLY_UP:
		setDx(0);
		setDy(2);
		if (flyUpDelay.isTerminated())
		{
			orbsState = ORBS_STATE_FLY_DOWN;
			flyDownDelay.start();
		}
		break;
	case ORBS_STATE_FALL:
		setDy(-2);
		setDx(0);
		if (getIsOnGround())
		{
			orbsState = ORBS_STATE_FLY_UP;
		}
		break;
	default:
		break;
	}
	setIsOnGround(false);
}

void Orbs::onCollision(MovableRect* other, float collisionTime, int nx, int ny)
{
	if (nx != 0 && other->getCollisionType() == COLLISION_TYPE_GROUND)
	{
		setDirection(nx);
	}
	Enemy::onCollision(other, collisionTime, nx, ny);
}
