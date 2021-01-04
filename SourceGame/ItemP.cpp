#include "ItemP.h"
#include "SpriteManager.h"

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
