#include "PlayerMiniBullet.h"
#include "SpriteManager.h"
#include "Sound.h"
PlayerMiniBullet::PlayerMiniBullet()
{
	setSprite(SpriteManager::getInstance()->getSprite(SPRITE_INFO_PLAYER_MINI_BULLET));
	Sound::getInstance()->play("PlayerFireArea2", false, 1);
	animationGameTime.init(500);
}

void PlayerMiniBullet::onUpdate(float dt)
{
	if (getFrameAnimation() == getLastFrameCurrentAnimation())
	{
		setPauseAnimation(true);
	}
}
