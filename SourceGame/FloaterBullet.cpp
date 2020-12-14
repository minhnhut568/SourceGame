#include "FloaterBullet.h"
#include "SpriteManager.h"

FloaterBullet::FloaterBullet()
{
	setSprite(SpriteManager::getInstance()->getSprite(SPRITE_INFO_FLOATER_BULLET));
	animationGameTime.init(500);
	setPhysicsEnable(false);
}

void FloaterBullet::onUpdate(float dt)
{
	if (getFrameAnimation() == getLastFrameCurrentAnimation())
	{
		setPauseAnimation(true);
	}
	AriseBase::onUpdate(dt);
}
