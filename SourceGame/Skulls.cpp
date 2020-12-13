#include "Skulls.h"
#include "SkullsBullet.h"
#include "Player.h"
#include<string>

Skulls::Skulls()
{
	startY = 0;
	setDirection(-1);
	setDx(-1);
	setDy(1);

	shootTime.init(S("skulls_shoot_time"));
	shootDelay.init(S("skulls_shoot_delay"));
}
void Skulls::onUpdate(float dt)
{
	shootDelay.update();

	if (shootTime.atTime())
	{
		TRACE("shoot");
		shootDelay.start();
		SkullsBullet* bullet = new SkullsBullet();
		bullet->setX(this->getMidX());
		bullet->setY(this->getMidY());

		auto player = Player::getInstance();

		auto xb = bullet->getX();
		auto yb = bullet->getY();
		auto xp = player->getX();
		auto yp = player->getY();
		auto r = S("Skulls_r");

		if (abs(yp - yb) <= 20)
		{
			if (getMidX() < player->getMidX())
			{
				bullet->setDx(r);
			}
			else
			{
				bullet->setDx(-r);
			}
		}
		else
		{
			auto m = ((xp - xb) * (xp - xb)) / ((yp - yb) * (yp - yb));

			auto dx = sqrt(r * r * m / (1 + m));

			if (getMidX() < player->getMidX())
			{
				bullet->setDx(dx);
			}
			else
			{
				bullet->setDx(-dx);
			}

			auto dy = sqrt(abs(r * r - dx * dx));

			if (getMidY() < player->getMidY())
			{
				bullet->setDy(dy);
			}
			else
			{
				bullet->setDy(-dy);
			}
		}
		auto xx = bullet->getDx();
		auto yy = bullet->getDy();
		TRACE_VAL_LN("dx", xx);
		TRACE_VAL_LN("dy", yy);
	}

	if (shootDelay.isOnTime())
	{
		setAnimation(SKULLS_ACTION_RELEASE);
	}
	else
	{
		setAnimation(SKULLS_ACTION_FLY);
	}

}

void Skulls::onCollision(MovableRect* other, float collisionTime, int nx, int ny)
{
	if (other->getCollisionType() == COLLISION_TYPE_GROUND)
	{
		if (nx != 0)
		{
			setDx(nx);
		}
		if (ny != 0)
		{
			setDy(ny);
		}
	}
}
