#include "Cannons.h"
#include "Cannons.h"
#include "FloaterBullet.h"

Cannons::Cannons()
{
	shootTime.init(S("cannons_shoot_time"));
	shootDelay.init(S("cannons_shoot_delay"));
	setDirection(-1);
	isVertical = true;
}

void Cannons::onUpdate(float dt)
{
	shootDelay.update();



	if (shootTime.atTime()) {
		FloaterBullet* bullet1 = new FloaterBullet();
		FloaterBullet* bullet2 = new FloaterBullet();
		bullet1->setX(this->getX() - 8);
		bullet1->setY(this->getY() - 3);
		bullet2->setX(this->getX() - 8);
		bullet2->setY(this->getY() - 3);

		if (isVertical)
		{
			bullet1->setDy(3);
			bullet1->setDx(0);

			bullet2->setDy(-3);
			bullet2->setDx(0);
		}
		else
		{
			bullet1->setDx(3);
			bullet1->setDy(0);

			bullet2->setDx(-3);
			bullet2->setDy(0);
		}

		isVertical = !isVertical;
	}
	

}

void Cannons::onCollision(MovableRect* other, float collisionTime, int nx, int ny)
{
}