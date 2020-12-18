#include "PlayerMiniOverWorldBullet.h"
#include "SpriteManager.h"
#include "Enemy.h"

void PlayerMiniOverWorldBullet::onUpdate(float dt)
{
	if (getDx() == 0 && getDy() == 0)
	{
		this->markForDelete = true;
	}
}

void PlayerMiniOverWorldBullet::onAABBCheck(MovableRect* other)
{
	if (other->getCollisionType() == COLLISION_TYPE_ENEMY)
	{
		((Enemy*)other)->setConflicBullet();
	}
}

PlayerMiniOverWorldBullet::PlayerMiniOverWorldBullet()
{
	setSprite(SpriteManager::getInstance()->getSprite(SPRITE_INFO_PLAYER_ONE_WORLD_BULLET));
	setWidth(getSprite()->image->Width);
	setWidth(getSprite()->image->Height);
	//setPhysicsEnable(false);
	setDirection(TEXTURE_DIRECTION_RIGHT);
}
