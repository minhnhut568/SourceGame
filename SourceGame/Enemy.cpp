#include "Enemy.h"
#include "Player.h"
#include "ItemP.h"

void Enemy::onCollision(MovableRect* other, float collisionTime, int nx, int ny)
{
	if (other->getCollisionType() == COLLISION_TYPE_GROUND)
	{
		preventMovementWhenCollision(collisionTime, nx, ny);
		PhysicsObject::onCollision(other, collisionTime, nx, ny);
	}
}

void Enemy::setDirectionFollowPlayer()
{
	if (getMidX() < Player::getInstance()->getMidX())
	{
		setDirection(TEXTURE_DIRECTION_RIGHT);
	}
	else
	{
		setDirection(TEXTURE_DIRECTION_LEFT);
	}
}

void Enemy::onUpdate(float dt)
{
	PhysicsObject::onUpdate(dt);
}

void Enemy::setConflicBullet(BaseObject* bullet)
{
	bullet->alive = false;
	alive = false;
	Sound::getInstance()->play("EnemyDie", false, 1);
	ItemP* item = new ItemP();
	item->setX(getX());
	item->setY(getY() + 16);
}
