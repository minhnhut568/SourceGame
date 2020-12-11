#include "Insect.h"

Insect::Insect()
{
	flyDownDelay.init(S("insect_flyDownDelay"));
	flyUpDelay.init(S("insect_flyUpDelay"));
	insectState = INSECT_STATE_FLY_DOWN;
	flyDownDelay.start();
	setDirection(-1);
}

void Insect::onUpdate(float dt)
{
	flyDownDelay.update();
	flyUpDelay.update();
	switch (insectState)
	{
	case INSECT_STATE_FLY_DOWN:
		setDx(getDirection());
		setDy(-1);
		if (flyDownDelay.isTerminated() || getIsOnGround())
		{
			insectState = INSECT_STATE_FLY_UP;
			flyUpDelay.start();
		}
		break;
	case INSECT_STATE_FLY_UP:
		setDx(0);
		setDy(2);
		if (flyUpDelay.isTerminated())
		{
			insectState = INSECT_STATE_FLY_DOWN;
			flyDownDelay.start();
		}
		break;
	case INSECT_STATE_FALL:
		setDy(-2);
		setDx(0);
		if (getIsOnGround())
		{
			insectState = INSECT_STATE_FLY_UP;
		}
		break;
	default:
		break;
	}
	setIsOnGround(false);
}

void Insect::onCollision(MovableRect* other, float collisionTime, int nx, int ny)
{
	if (nx != 0)
	{
		setDirection(nx);
	}
	if (ny == -1)
	{
		insectState = INSECT_STATE_FALL;
	}
	Enemy::onCollision(other, collisionTime, nx, ny);
}
