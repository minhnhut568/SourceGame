#include "PlayerMiniBullet.h"
#include "SpriteManager.h"
PlayerMiniBullet::PlayerMiniBullet()
{
	setSprite(SpriteManager::getInstance()->getSprite(SPRITE_INFO_PLAYER_MINI_BULLET));
	animationGameTime.init(500);
}

void PlayerMiniBullet::onUpdate(float dt)
{
	if (getFrameAnimation() == getLastFrameCurrentAnimation())
	{
		setPauseAnimation(true);
	}
}
