#include "Skulls.h"
#include "DelayTime.h"
#include "SkullsBullet.h"
#include "Player.h"




Skulls::Skulls()
{
	setDirection(-1);
	standDelay.init(S("skulls_stand_delay"));
	runDelay.init(S("skulls_run_delay"));
	skullsState = SKULLS_STATE_RUN;
	runDelay.start();
}
bool Skulls::checkContactPlayer()
{
	auto player = Player::getInstance();
	if (getleft() < player->getRight() && getRight() > player->getleft()) {
		return true;
	}
	return false;
}
void Skulls::onUpdate(float dt)
{
	standDelay.update();
	runDelay.update();
	switch (skullsState)
	{
	case SKULLS_STATE_RUN:
		setDx(getDirection() * S("skulls_dx"));
		if (!runDelay.isOnTime())
		{
			if (checkContactPlayer())
			{
				skullsState = SKULLS_STATE_STAND;
				standDelay.start();
				auto bullet = new SkullsBullet();
				bullet->setX(getX());
				bullet->setY(getY());

			}
		}
		break;
	case SKULLS_STATE_STAND:
		setDx(0);
		if (!standDelay.isOnTime())
		{
			if (checkContactPlayer())
			{
				skullsState = SKULLS_STATE_RUN;
				runDelay.start();
			}
		}
		break;
	default:
		break;
	}

}

void Skulls::onCollision(MovableRect* other, float collisionTime, int nx, int ny)
{
	if (other->getCollisionType() == COLLISION_TYPE_GROUND)
	{
		if (nx != 0)
		{
			setDirection(nx);
		}
	}
}
