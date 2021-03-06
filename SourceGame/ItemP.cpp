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
	PhysicsObject::setAy(0); // treo item P
}

void ItemP::onCollision(MovableRect* other, float collisionTime, int nx, int ny)
{
	preventMovementWhenCollision(collisionTime, nx, ny);
}

void ItemP::onAABBCheck(MovableRect* other)
{
	if (other == Player::getInstance())
	{
		Sound::getInstance()->play("PickingItems", false, 1);
		this->alive = false;
		Scorebar::getInstance()->decreaseHealth(-1);
	}
}
