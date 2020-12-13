#include "SkullsBullet.h"
#include "PlayerBullet.h"
#include "SpriteManager.h"
#include "Enemy.h"

SkullsBullet::SkullsBullet()
{
	setSprite(SpriteManager::getInstance()->getSprite(SPRITE_INFO_SKULLS_BULLET));
	animationGameTime.init(500);
}

void SkullsBullet::onUpdate(float dt)
{
	if (getFrameAnimation() == getLastFrameCurrentAnimation())
	{
		setPauseAnimation(true);
	}
}
