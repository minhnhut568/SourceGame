#include "ItemP.h"
#include "SpriteManager.h"
#include "Player.h"
#include"Scorebar.h"

ItemP::ItemP()
{
	setSprite(SpriteManager::getInstance()->getSprite(SPRITE_INFO_ITEM_P));
	setWidth(getSprite()->image->Width);
	setHeight(getSprite()->image->Height);
	setDirection(TEXTURE_DIRECTION_LEFT);
	setCollisionType(COLLISION_TYPE::COLLISION_TYPE_ITEM);
}

void ItemP::onCollision(MovableRect* other, float collisionTime, int nx, int ny)
{
	preventMovementWhenCollision(collisionTime, nx, ny);
}

void ItemP::onAABBCheck(MovableRect* other)
{
	if (other == Player::getInstance())
	{
		this->alive = false;
		Scorebar::getInstance()->decreaseHealth(-1);
	}
}
