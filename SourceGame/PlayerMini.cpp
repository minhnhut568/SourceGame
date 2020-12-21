#include "PlayerMini.h"
#include "SpriteManager.h"
#include "KEY.h"
#include "Player.h"
#include "Collision.h"
#include "PlayerMiniBullet.h"
#include "Game.h"
#include "Scorebar.h"

PlayerMini::PlayerMini()
{
	setSprite(SPR(SPRITE_INFO_PLAYER_MINI));
	setDirection(TEXTURE_DIRECTION::TEXTURE_DIRECTION_RIGHT);
	bulletDelay.init(S("player_bulle_delay"));

	blinkTime.init(S("player_blink_time"));
	blinkDelay.init(S("player_blink_delay"));
	blinkCantControlDelay.init(S("player_blink_can't_control_delay"));
	setCollisionType(COLLISION_TYPE::COLLISION_TYPE_PLAYER);
	ladder = 0;
	playerMiniState = PLAYER_MINI_STATE_NORMAL;
}

void PlayerMini::onUpdate(float dt)
{
	blinkDelay.update();
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

	if (playerMiniState == PLAYER_MINI_STATE_ON_LADDER)
	{
		setDy(0);
		setPauseAnimation(true);
		if (keyUpDown)
		{
			setDy(1);
			setPauseAnimation(false);
		}
		if (keyDownDown)
		{
			setDy(-1);
			setPauseAnimation(false);
		}
		setAnimation(PLAYER_MINI_ACTION::PLAYER_MINI_ACTION_CLIMB);

		if (ladder != 0 && ((getDy() > 0 && getTop() + getDy() > ladder->getTop()) || (getDy() < 0 && getBottom() + getDy() < ladder->getBottom())))
		{
			ladder = 0;
			playerMiniState = PLAYER_MINI_STATE_NORMAL;
		}

		return;
	}

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
	if (other->getCollisionType() == COLLISION_TYPE_GROUND && playerMiniState == PLAYER_MINI_STATE_NORMAL)
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
		Scorebar::getInstance()->decreaseHealth(1);
	}

	if (other->getCollisionType() == COLLISION_TYPE_GATE_OVER_WORLD_SPACE0)
	{
		if (KEY::getInstance()->isDownDown)
		{
			Game::getInstance()->setWorldType(WorldType::WT_OVER_WORLD_SPACE0);
			Game::getInstance()->overWorld->setCurrentSpace(0);
			Game::getInstance()->overWorld->resetLocationInSpace();
		}
	}
	if (other->getCollisionType() == COLLISION_TYPE_GATE_OVER_WORLD_SPACE1)
	{
		if (KEY::getInstance()->isDownDown)
		{
			Game::getInstance()->setWorldType(WorldType::WT_OVER_WORLD_SPACE1);
			Game::getInstance()->overWorld->setCurrentSpace(1);
			Game::getInstance()->overWorld->resetLocationInSpace();
		}
	}
	if (other->getCollisionType() == COLLISION_TYPE_GATE_OVER_WORLD_SPACE2)
	{
		if (KEY::getInstance()->isDownDown)
		{
			Game::getInstance()->setWorldType(WorldType::WT_OVER_WORLD_SPACE2);
			Game::getInstance()->overWorld->setCurrentSpace(2);
			Game::getInstance()->overWorld->resetLocationInSpace();
		}
	}

	if (other->getCollisionType() == COLLISION_TYPE_LADDER)
	{
		if (KEY::getInstance()->isUpDown || KEY::getInstance()->isDownDown)
		{
			ladder = other;
			if ((KEY::getInstance()->isUpDown && getTop() + 1 > ladder->getTop()) || (KEY::getInstance()->isDownDown && getBottom() - 1 < ladder->getBottom()))
			{
				ladder = 0;
				return;
			}
			setDirection(1);
			playerMiniState = PLAYER_MINI_STATE_ON_LADDER;
			setX(ladder->getMidX() - getWidth() / 2 + 2);
		}
	}
}
