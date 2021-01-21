#include "PlayerBullet.h"
#include "SpriteManager.h"
#include "Enemy.h"
#include "Explosion.h"
#include "Sound.h"

void PlayerBullet::onUpdate(float dt)
{
	if (getDx() == 0 && getDy() == 0)
	{
		this->markForDelete = true;
	}
}

void PlayerBullet::onAABBCheck(MovableRect* other)
{
	if (other->getCollisionType() == COLLISION_TYPE_ENEMY)
	{
		((BaseObject*)other)->setConflicBullet(this);
	}
}

PlayerBullet::PlayerBullet()
{
	setSprite(SpriteManager::getInstance()->getSprite(SPRITE_INFO_BULLET));
	setWidth(getSprite()->image->Width);
	setHeight(getSprite()->image->Height);
	setDirection(TEXTURE_DIRECTION_RIGHT);
	Sound::getInstance()->play("PlayerFireArea2", false, 1);
}

void PlayerBullet::onCollision(MovableRect* other, float collisionTime, int nx, int ny)
{
	if (other->getCollisionType() == COLLISION_TYPE_GROUND)
	{
		/* ngăn chặn di chuyển */
		preventMovementWhenCollision(collisionTime, nx, ny);
		PhysicsObject::onCollision(other, collisionTime, nx, ny);
		Explosion::setExplosion(this);

	}
}
