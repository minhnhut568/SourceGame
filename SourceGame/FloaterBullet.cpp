#include "FloaterBullet.h"
#include "SpriteManager.h"
#include"Player.h"
#include"Explosion.h"

FloaterBullet::FloaterBullet()
{
	setSprite(SpriteManager::getInstance()->getSprite(SPRITE_INFO_FLOATER_BULLET));
	animationGameTime.init(500);
	setPhysicsEnable(false);
}

void FloaterBullet::onAABBCheck(MovableRect* other)
{
	if (other == Player::getInstance())
	{
		markForDelete = true;
		Explosion::setExplosion(this);
	}
}

void FloaterBullet::onUpdate(float dt)
{
	if (getFrameAnimation() == getLastFrameCurrentAnimation())
	{
		setPauseAnimation(true);
	}
	AriseBase::onUpdate(dt);
}
