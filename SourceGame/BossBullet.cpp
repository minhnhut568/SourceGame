#include "BossBullet.h"
#include "SpriteManager.h"
#include"Player.h"
#include"PlayerOverWorld.h"
#include"Explosion.h"

BossBullet::BossBullet()
{
	setSprite(SpriteManager::getInstance()->getSprite(SPRITE_INFO_BOSS_BULLET));
	animationGameTime.init(500);
	setPhysicsEnable(false);
	setCollisionType(COLLISION_TYPE_ENEMY);
}

void BossBullet::onAABBCheck(MovableRect* other)
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

void BossBullet::onUpdate(float dt)
{
	if (getFrameAnimation() == getLastFrameCurrentAnimation())
	{
		setPauseAnimation(true);
	}
	AriseBase::onUpdate(dt);
}

void BossBullet::onCollision(MovableRect* other, float collisionTime, int nx, int ny)
{
	if (other->getCollisionType() == COLLISION_TYPE_GROUND)
	{
		/* ngăn chặn di chuyển */
		preventMovementWhenCollision(collisionTime, nx, ny);
		PhysicsObject::onCollision(other, collisionTime, nx, ny);
	}
}
