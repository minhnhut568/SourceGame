#include "BossClaw.h"
#include"SpriteManager.h"

BossClaw::BossClaw()
{
	setSprite(SpriteManager::getInstance()->getSprite(SPRITE_INFO_BOSS_BODY));
	setAnimation(0);
	relativeX = 0;
	relativeY = 0;
	inmortal = true;
	setDx(0);
	setDy(0);
}

void BossClaw::onUpdate(float dt)
{
}
