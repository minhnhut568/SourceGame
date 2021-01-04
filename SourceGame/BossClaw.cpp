#include "BossClaw.h"
#include"SpriteManager.h"
#include"Boss.h"
#include"PlayerOverWorld.h"
#include"Scorebar.h"
#include<string>

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

void BossClaw::render()
{
	if (Boss::getInstance()->alive)
	{
		AriseBase::render();
	}
}

void BossClaw::onAABBCheck(MovableRect* other)
{
	auto player = PlayerOverWorld::getInstance();
	if (Boss::getInstance()->alive && other == player)
	{
		if (!player->blinkDelay.isOnTime())
		{
			TRACE_VAL_LN("onAABBCheck PlayerOverWorld", 0);
			player->blinkDelay.start();
			player->blinkCantControlDelay.start();
			Scorebar::getInstance()->decreaseHealth(1);
		}
	}
}
