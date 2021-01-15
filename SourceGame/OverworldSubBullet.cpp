#include "OverworldSubBullet.h"
#include "SpriteManager.h"
#include<string>
void OverworldSubBullet::onUpdate(float dt)
{
	shootingDelay.update();
	beforeExplosionDelay.update();
	explosingDelay.update();
	TRACE_VAL_LN("OverworldSubBullet_ONUPDATE", (GetTickCount() - shootingDelay.startTime));

	switch (state)
	{
	case PLAYERMINI_BULLET_STATE_SHOOTING:
		setAnimation(PLAYERMINI_BULLET_ANIMATION_SHOOTING);
		if (shootingDelay.isTerminated())
		{
			state = PLAYERMINI_BULLET_STATE_BEFORE_EXPLOSION;
			beforeExplosionDelay.start();
		}
		break;
	case PLAYERMINI_BULLET_STATE_BEFORE_EXPLOSION:
		setAnimation(PLAYERMINI_BULLET_ANIMATION_BEFORE_EXPLOSION);
		setDx(0);
		setDy(0);
		if (beforeExplosionDelay.isTerminated())
		{
			state = PLAYERMINI_BULLET_STATE_EXPLOSION;
			explosingDelay.start();
		}
		break;
	case PLAYERMINI_BULLET_STATE_EXPLOSION:
		setAnimation(PLAYERMINI_BULLET_ANIMATION_EXPLOSION);
		if (explosingDelay.isTerminated())
		{
			markForDelete = true;
		}
		break;
	default:
		break;
	}
}

void OverworldSubBullet::onAABBCheck(MovableRect* other)
{
}

OverworldSubBullet::OverworldSubBullet()
{
	shootingDelay.init(S("overworld-sub-shooting-delay"));
	beforeExplosionDelay.init(S("overworld-sub-before-explosion-delay"));
	explosingDelay.init(S("overworld-sub-explosion-delay"));
	setSprite(SpriteManager::getInstance()->getSprite(SPRITE_INFO_OVERWORLD_BULLET));
	setWidth(getSprite()->image->Width);
	setHeight(getSprite()->image->Height);
	setDirection(TEXTURE_DIRECTION_LEFT);
	shootingDelay.start();
}
