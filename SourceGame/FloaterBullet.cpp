#include "FloaterBullet.h"
#include "SpriteManager.h"
#include"Player.h"
#include"PlayerOverWorld.h"
#include"Explosion.h"

FloaterBullet::FloaterBullet()
{
	setSprite(SpriteManager::getInstance()->getSprite(SPRITE_INFO_FLOATER_BULLET));
	animationGameTime.init(500);
	setPhysicsEnable(false);
	setCollisionType(COLLISION_TYPE_ENEMY);
}

void FloaterBullet::onAABBCheck(MovableRect* other)
{
	if (other == Player::getInstance())
	{
		markForDelete = true;
		Explosion::setExplosion(this);
	}

	if (other == PlayerOverWorld::getInstance())
	{
		markForDelete = true;
		Explosion::setExplosion(this);
	}

}

void FloaterBullet::onUpdate(float dt)
{
	if (getFrameAnimation() == getLastFrameCurrentAnimation())
	{
		setPauseAnimation(true);
	}
	AriseBase::onUpdate(dt);
}

void FloaterBullet::onCollision(MovableRect* other, float collisionTime, int nx, int ny)
{
	if (other->getCollisionType() == COLLISION_TYPE_GROUND)
	{
		/* ngăn chặn di chuyển */
		markForDelete = true;
		preventMovementWhenCollision(collisionTime, nx, ny);
		PhysicsObject::onCollision(other, collisionTime, nx, ny);
	}
}
