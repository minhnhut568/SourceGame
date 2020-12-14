#include "Explosion.h"
#include"SpriteManager.h"

void Explosion::setExplosion(BaseObject* obj)
{
	Explosion* explosion = new Explosion();
	explosion->setX(obj->getMidX());
	explosion->setY(obj->getMidY());
}

Explosion::Explosion()
{
	setSprite(SpriteManager::getInstance()->getSprite(SPRITE_INFO_BOOM));
	setPhysicsEnable(false);
	setDirection(1);
}

void Explosion::onUpdate(float dt)
{
	AriseBase::onUpdate(dt);
	if (getIsLastFrameAnimationDone())
	{
		markForDelete = true;
	}

}
