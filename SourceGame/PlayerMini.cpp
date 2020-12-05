#include "PlayerMini.h"
#include "SpriteManager.h"
#include "KEY.h"
#include "Player.h"
#include "Collision.h"
#include "PlayerMiniBullet.h"

PlayerMini::PlayerMini()
{
	setSprite(SPR(SPRITE_INFO_PLAYER_MINI));
	setDirection(TEXTURE_DIRECTION::TEXTURE_DIRECTION_RIGHT);
	bulletDelay.init(S("player_bulle_delay"));

	blinkTime.init(S("player_blink_time"));
	blinkDelay.init(S("player_blink_delay"));
	blinkCantControlDelay.init(S("player_blink_can't_control_delay"));
}

void PlayerMini::onUpdate(float dt)
{
	if (blinkDelay.isOnTime())
	{
		if (blinkTime.atTime())
		{
			setRenderActive(false);
		}
		else
		{
			setRenderActive(true);
		}
	}
	else
	{
		setRenderActive(true);
	}

	bulletDelay.update();
	bool keyLeftDown, keyRightDown, keyUpDown, keyDownDown, keyJumpPress;
	keyLeftDown = KEY::getInstance()->isLeftDown;
	keyRightDown = KEY::getInstance()->isRightDown;
	keyUpDown = KEY::getInstance()->isUpDown;
	keyDownDown = KEY::getInstance()->isDownDown;
	keyJumpPress = KEY::getInstance()->isJumpPress;
	auto changePlayerDown = KEY::getInstance()->changePlayer;

	float vx = GLOBALS_D("player_vx");

	/* nếu giữ key trái */
	if (keyLeftDown)
	{
		/* set animation chạy */
		setVx(-vx);
		setDirection(TEXTURE_DIRECTION_LEFT);
	}
	/* nếu giữ key phải */
	else if (keyRightDown)
	{
		/* set animation chạy */
		setVx(vx);
		setDirection(TEXTURE_DIRECTION_RIGHT);
	}
	else
	{
		/* set animation đứng yên */
		setVx(0);
	}

	if (getIsOnGround())
	{
		if (getVx() != 0)
		{
			setAnimation(PLAYER_MINI_ACTION_RUN);
		}
		else
		{
			setAnimation(PLAYER_MINI_ACTION_STAND);
		}

		if (keyJumpPress)
		{
			setVy(GLOBALS_D("player_vy_jump"));
		}
	}
	else
	{
		setAnimation(PLAYER_MINI_ACTION_JUMP);
	}

	if (KEY::getInstance()->isAttackDown && !bulletDelay.isOnTime())
	{
		PlayerMiniBullet* bullet = new PlayerMiniBullet();
		bullet->setDirection(getDirection());

		bullet->setY(getMidY());
		if (getDirection() == 1)
		{
			bullet->setX(getRight());
		}
		else
		{
			bullet->setX(getleft());
		}
		bullet->setDx(getDirection() * S("playerbullet_dx"));
		bullet->setDy(0);
		bullet->setAnimation(BULLET_ANIMATION_HOR);

		bulletDelay.start();
	}

	if (changePlayerDown && Collision::AABBCheck(Player::getPlayerMain(), Player::getPlayerMini()))
	{
		Player::changeToPlayerMain();
	}


	PhysicsObject::onUpdate(dt);
}

void PlayerMini::onCollision(MovableRect* other, float collisionTime, int nx, int ny)
{
	if (other->getCollisionType() == COLLISION_TYPE_GROUND)
	{
		/* ngăn chặn di chuyển */
		preventMovementWhenCollision(collisionTime, nx, ny);
		PhysicsObject::onCollision(other, collisionTime, nx, ny);
	}
}

void PlayerMini::onAABBCheck(MovableRect* other)
{
	if (other->getCollisionType() == COLLISION_TYPE::COLLISION_TYPE_ENEMY && !blinkDelay.isOnTime())
	{
		blinkDelay.start();
		blinkCantControlDelay.start();
		setVx(S("player_blink_vx"));
	}
}
