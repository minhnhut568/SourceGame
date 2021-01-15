#include "Worm.h"
#include "Player.h"

Worm::Worm()
{
	setAnimation(WORM_ACTION::WORM_ACTION_RUN);
	setAy(S("worm_ay"));
	startY = 0;
	wormState = WORM_STATE::WORM_STATE_RUN;
	setDirection(-1);
}

void Worm::onUpdate(float dt)
{
	auto player = Player::getInstance();
	switch (wormState)
	{
	case WORM_STATE_RUN:
		if (getleft() > player->getRight() && getDirection() == 1)
		{
			setDirection(-1);
		}

		if (getRight() < player->getleft() && getDirection() == -1)
		{
			setDirection(1);
		}

		setVx(S("worm_vx") * getDirection());
		break;
	case WORM_STATE_JUMP:
		if (getY() - startY > S("worm_y_climp")) //16px
		{
			wormState = WORM_STATE_RUN;
			setPhysicsEnable(true);
		}
		break;
	default:
		break;
	}

	//if (getIsOnGround())
	//{
	//	setPhysicsEnable(false);
	//}

	Enemy::onUpdate(dt);
}

void Worm::onCollision(MovableRect* other, float collisionTime, int nx, int ny)
{
	if (getIsOnGround() && nx != 0)
	{
		setDy(S("worm_dy"));
		setPhysicsEnable(false);
		startY = getY(); //Dung vo gach
		wormState = WORM_STATE_JUMP;
	}
	Enemy::onCollision(other, collisionTime, nx, ny);
}
