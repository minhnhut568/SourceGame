#include "Floater.h"
#include "Player.h"

Floater::Floater()
{
	setAnimation(FLOATER_STATE::FLOATER_STATE_FLY);
	setAy(S("floater_ay"));
	startY = 0;
	floaterState = FLOATER_STATE::FLOATER_STATE_FLY;
	setDirection(-1);
}

void Floater::onUpdate(float dt)
{
	auto player = Player::getInstance();
	switch (floaterState)
	{
	case FLOATER_STATE_FLY:
		if (getleft() > player->getRight() && getDirection() == 1)
		{
			setDirection(-1);
		}

		if (getRight() < player->getleft() && getDirection() == -1)
		{
			setDirection(1);
		}

		setVx(S("floater_vx") * getDirection());
		break;
	case FLOATER_STATE_SHOOT:
		
		break;
	default:
		break;
	}

	Enemy::onUpdate(dt);
}

void Floater::onCollision(MovableRect* other, float collisionTime, int nx, int ny)
{
	if (getIsOnGround() && nx != 0)
	{
		setDy(S("worm_dy"));
		setPhysicsEnable(false);
		startY = getY();
		floaterState = FLOATER_STATE_FLY;
	}
	Enemy::onCollision(other, collisionTime, nx, ny);
}
