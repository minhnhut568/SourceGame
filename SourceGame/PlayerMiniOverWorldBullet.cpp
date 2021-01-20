#include "PlayerMiniOverWorldBullet.h"
#include "SpriteManager.h"
#include "Enemy.h"
#include "Sound.h"

void PlayerMiniOverWorldBullet::onUpdate(float dt)
{
	if (getDx() == 0 && getDy() == 0)
	{
		this->markForDelete = true;
	}
	if (getFrameAnimation() == getLastFrameCurrentAnimation())
	{
		setPauseAnimation(true);
	}
}

void PlayerMiniOverWorldBullet::onAABBCheck(MovableRect* other)
{
	if (other->getCollisionType() == COLLISION_TYPE_ENEMY)
	{
		((BaseObject*)other)->setConflicBullet(this);
	}

	if (other->getCollisionType() == 7)
	{
		((BaseObject*)other)->alive = false;
		this->markForDelete = true;
	}
}

PlayerMiniOverWorldBullet::PlayerMiniOverWorldBullet()
{
	setSprite(SpriteManager::getInstance()->getSprite(SPRITE_INFO_PLAYER_OVER_WORLD_BULLET));
	setWidth(getSprite()->image->Width);
	setWidth(getSprite()->image->Height);
	//setPhysicsEnable(false);
	setDirection(TEXTURE_DIRECTION_RIGHT);
	Sound::getInstance()->play("PlayerFireOverWorld", false, 1);
	//animationGameTime.init(500);
}
