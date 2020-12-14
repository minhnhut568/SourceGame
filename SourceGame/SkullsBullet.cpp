#include "SkullsBullet.h"
#include "PlayerBullet.h"
#include "SpriteManager.h"
#include "Enemy.h"
#include"Explosion.h"

SkullsBullet::SkullsBullet()
{
	setSprite(SpriteManager::getInstance()->getSprite(SPRITE_INFO_SKULLS_BULLET));
	setWidth(10);
	setHeight(10);
	liveDelay.init(S("skulls_bullet_live_delay"));
}

void SkullsBullet::onUpdate(float dt)
{
	liveDelay.update();
	if (liveDelay.isTerminated())
	{
		markForDelete = true;
		Explosion::setExplosion(this);
	}
	AriseBase::onUpdate(dt);
}

void SkullsBullet::onCollision(MovableRect* other, float collisionTime, int nx, int ny)
{
	if (other->getCollisionType() == COLLISION_TYPE_GROUND)
	{
		preventMovementWhenCollision(collisionTime, nx, ny);
		if (ny == 1 && !liveDelay.isOnTime()) {
			liveDelay.start();
		}
	}
}
