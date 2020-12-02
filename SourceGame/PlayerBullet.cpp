#include "PlayerBullet.h"
#include "SpriteManager.h"

void PlayerBullet::onUpdate(float dt)
{
	if (getDx() == 0 && getDy() == 0)
	{
		this->markForDelete = true;
	}
}

PlayerBullet::PlayerBullet()
{
	setSprite(SpriteManager::getInstance()->getSprite(SPRITE_INFO_BULLET));
	setWidth(getSprite()->image->Width);
	setWidth(getSprite()->image->Height);
	//setPhysicsEnable(false);
	setDirection(TEXTURE_DIRECTION_RIGHT);
}
