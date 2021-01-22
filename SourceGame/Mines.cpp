#include "Mines.h"
#include "FloaterBullet.h"
#include "Explosion.h"
#include "Player.h"
Mines::Mines()
{
	Sound::getInstance()->play("MineBip", true, 0);
}

void Mines::onUpdate(float dt)
{
	auto player = Player::getInstance();

	//if (getX() == player->getX())
	//{
	//	
	//}
	//AriseBase::onUpdate(dt);
}
void Mines::onCollision(MovableRect* other, float collisionTime, int nx, int ny)
{
	Explosion::setExplosion(this);
	Sound::getInstance()->stop("MineBip");
	FloaterBullet* bullet1 = new FloaterBullet();
	FloaterBullet* bullet2 = new FloaterBullet();
	FloaterBullet* bullet3 = new FloaterBullet();
	FloaterBullet* bullet4 = new FloaterBullet();

	bullet1->setX(this->getX() - 13);
	bullet2->setX(this->getX() - 20);
	bullet3->setX(this->getX() + 10);
	bullet4->setX(this->getX() + 4);

	bullet1->setY(this->getY() + 3);
	bullet2->setY(this->getY() + 1);
	bullet3->setY(this->getY() + 1);
	bullet4->setY(this->getY() + 3);

	bullet1->setDy(-4);
	bullet2->setDy(-4);
	bullet3->setDy(-4);
	bullet4->setDy(-4);
}