#include "Domes.h"
#include "Player.h"

Domes::Domes()
{
	moveX = -1;
	moveY = 0;
	initNx = 0;
	initNy = 1;
	domesState = DOMES_STATE_RUN;
	ground = 0;
	setDirection(-1);
}

void Domes::onUpdate(float dt)
{
	auto player = Player::getInstance();
	switch (domesState)
	{
	case DOMES_STATE_RUN:
	{
		// di xung quanh
		if (ground != 0)
		{
			if ((moveY == 1 && getBottom() > ground->getTop()) || (moveY == -1 && getTop() < ground->getBottom()))
			{
				moveY = 0;
				if (getleft() < ground->getleft())
				{
					moveX = 1;
				}
				else
				{
					moveX = -1;
				}
			}

			if ((moveX == 1 && getleft() > ground->getRight()) || (moveX == -1 && getRight() < ground->getleft()))
			{
				moveX = 0;
				if (getTop() > ground->getTop())
				{
					moveY = -1;
				}
				else
				{
					moveY = 1;
				}
			}

			if (moveX != 0) 
			{
				if (getTop() > ground->getTop()) {
					setAnimation(DOMES_UP);
				}
				if (getBottom() < ground->getBottom()) {
					setAnimation(DOMES_DOWN);
					if (getleft() == (player->getRight() - 25))
						domesState = DOMES_STATE_WAIT;
				}
			}
			if (moveY != 0)
			{
				if (getRight() > ground->getRight()) {
					setAnimation(DOMES_RIGHT);
				}
				if (getleft() < ground->getleft()) {
					setAnimation(DOMES_LEFT);
				}
			}

			auto vol = S("domes_dx");
			setDx(moveX * vol);
			setDy(moveY * vol);
		}
		else
		{
			setDx(-initNx);
			setDy(-initNy);
		}

		break;
	}
	case DOMES_STATE_WAIT:
		setDx(0);
		setDy(0);
		domesState = DOMES_STATE_FIRE;
		break;
	case DOMES_STATE_FIRE:
		setDy(-(player->getRight()));
		break;
	default:
		break;
	}
}

void Domes::onCollision(MovableRect* other, float collisionTime, int nx, int ny)
{
	if (other->getCollisionType() == COLLISION_TYPE_GROUND)
	{
		if (ground != 0)
		{
			if (ny != 0)
			{
				moveY = 0;
				if (ground->getleft() < getleft())
				{
					moveX = 1;
				}
				else
				{
					moveX = -1;
				}
			}

			if (nx != 0)
			{
				moveX = 0;
				if (ground->getTop() > getTop())
				{
					moveY = -1;
				}
				else
				{
					moveY = 1;
				}
			}
		}

		ground = other;
	}

	Enemy::onCollision(other, collisionTime, nx, ny);
}
