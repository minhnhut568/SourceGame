#include "PlayerOverWorld.h"
#include "PlayerMiniOverWorldBullet.h"
#include "Game.h"
#include "Scorebar.h"
#include "Player.h"
#include "SpriteManager.h"
#include "KEY.h"
#include "Collision.h"
#include "OverworldSubBullet.h"


PlayerOverWorld* PlayerOverWorld::instance = 0;
PlayerOverWorld* PlayerOverWorld::getInstance()
{
	if (PlayerOverWorld::instance == 0)
	{
		PlayerOverWorld::instance = new PlayerOverWorld();
	}
	return PlayerOverWorld::instance;
}

void PlayerOverWorld::onUpdate(float dt)
{
	blinkDelay.update();
	shootDelay.update();
	bool keyLeftDown, keyRightDown, keyUpDown, keyDownDown;
	/* kiểm tra key bên trái có được giữ */
	keyLeftDown = KEY::getInstance()->isLeftDown;
	/* kiểm tra key bên phải có được giữ */
	keyRightDown = KEY::getInstance()->isRightDown;
	keyUpDown = KEY::getInstance()->isUpDown;
	keyDownDown = KEY::getInstance()->isDownDown;

	if (KEY::getInstance()->isAttackDown)
	{
		if (!shootDelay.isOnTime())
		{
			PlayerMiniOverWorldBullet* bullet = new PlayerMiniOverWorldBullet();
			bullet->setX(getMidX());
			bullet->setY(getMidY());

			if (this->playerDirection == PLAYER_OW_DIRECTION_RIGHT)
			{
				bullet->setDx(S("player-bullet-over-world-dx"));
			}

			if (this->playerDirection == PLAYER_OW_DIRECTION_LEFT)
			{
				bullet->setDx(-S("player-bullet-over-world-dx"));
			}

			if (this->playerDirection == PLAYER_OW_DIRECTION_UP)
			{
				bullet->setDy(S("player-bullet-over-world-dx"));
			}

			if (this->playerDirection == PLAYER_OW_DIRECTION_DOWN)
			{
				bullet->setDy(-S("player-bullet-over-world-dx"));
			}

			shootDelay.start();
		}
	}

	if (KEY::getInstance()->isSubWeaponDown)
	{
		if (!shootDelay.isOnTime())
		{
			OverworldSubBullet* bullet = new OverworldSubBullet();
			bullet->setX(getMidX());
			bullet->setY(getMidY());

			if (this->playerDirection == PLAYER_OW_DIRECTION_RIGHT)
			{
				bullet->setDx(S("player-bullet-over-world-dx"));
			}

			if (this->playerDirection == PLAYER_OW_DIRECTION_LEFT)
			{
				bullet->setDx(-S("player-bullet-over-world-dx"));
			}

			if (this->playerDirection == PLAYER_OW_DIRECTION_UP)
			{
				bullet->setDy(S("player-bullet-over-world-dx"));
			}

			if (this->playerDirection == PLAYER_OW_DIRECTION_DOWN)
			{
				bullet->setDy(-S("player-bullet-over-world-dx"));
			}

			shootDelay.start();
		}
	}
	setPauseAnimation(false);
	if (keyLeftDown)
	{
		setPlayerDirection(PLAYER_OW_DIRECTION_LEFT);
	}
	else if (keyRightDown)
	{
		setPlayerDirection(PLAYER_OW_DIRECTION_RIGHT);
	}
	else if (keyUpDown)
	{
		setPlayerDirection(PLAYER_OW_DIRECTION_UP);
	}
	else if (keyDownDown)
	{
		setPlayerDirection(PLAYER_OW_DIRECTION_DOWN);
	}
	else
	{
		moveX = 0;
		moveY = 0;
		setPauseAnimation(true);
		setFrameAnimation(0);
	}

	setDx(moveX * S("player-one-world-dx"));
	setDy(moveY * S("player-one-world-dx"));


}

void PlayerOverWorld::onCollision(MovableRect * other, float collisionTime, int nx, int ny)
{
	if (other->getCollisionType() == COLLISION_TYPE_GROUND || other->getCollisionType() == 7)
	{
		/* ngăn chặn di chuyển */
		preventMovementWhenCollision(collisionTime, nx, ny);
		PhysicsObject::onCollision(other, collisionTime, nx, ny);
	}
}

void PlayerOverWorld::onAABBCheck(MovableRect* other)
{
	if (other->getCollisionType() == COLLISION_TYPE::COLLISION_TYPE_ENEMY && !blinkDelay.isOnTime())
	{
		blinkDelay.start();
		blinkCantControlDelay.start();
		Scorebar::getInstance()->decreaseHealth(1);
	}

	if (other->getCollisionType() == COLLISION_TYPE_GATE_TO_WORLD_SPACE6)
	{
		if (KEY::getInstance()->isEnterDown)
		{
			Game::getInstance()->setWorldType(WorldType::WT_WORLD);
			Game::getInstance()->world->setCurrentSpace(6);
			Game::getInstance()->world->resetLocationInSpace();
		}
	}
	if (other->getCollisionType() == COLLISION_TYPE_GATE_TO_WORLD_SPACE4)
	{
		if (KEY::getInstance()->isEnterDown)
		{
			Game::getInstance()->setWorldType(WorldType::WT_WORLD);
			Game::getInstance()->world->setCurrentSpace(4);
			Game::getInstance()->world->resetLocationInSpace();
		}
	}
	if (other->getCollisionType() == COLLISION_TYPE_GATE_TO_WORLD_SPACE5)
	{
		if (KEY::getInstance()->isEnterDown)
		{
			Game::getInstance()->setWorldType(WorldType::WT_WORLD);
			Game::getInstance()->world->setCurrentSpace(5);
			Game::getInstance()->world->resetLocationInSpace();
		}
	}

	if (other->getCollisionType() == 6)
	{
		Game::getInstance()->worldType = WT_OVER_WORLD_SPACE0;
		Game::getInstance()->overWorld->setCurrentSpace(3);
		Game::getInstance()->overWorld->resetLocationInSpace();
	}

}

void PlayerOverWorld::setPlayerDirection(PLAYER_OW_DIRECTION direction)
{
	this->playerDirection = direction;
	switch (direction)
	{
	case PLAYER_OW_DIRECTION_LEFT:
		setDirection(-1);
		setAnimation(PLAYER_OW_ACTION_LEFT_RUN);
		moveX = -1;
		moveY = 0;
		break;
	case PLAYER_OW_DIRECTION_RIGHT:
		setDirection(1);
		setAnimation(PLAYER_OW_ACTION_LEFT_RUN);
		moveX = 1;
		moveY = 0;
		break;
	case PLAYER_OW_DIRECTION_UP:
		setAnimation(PLAYER_OW_ACTION_UP_RUN);
		moveX = 0;
		moveY = 1;
		break;
	case PLAYER_OW_DIRECTION_DOWN:
		setAnimation(PLAYER_OW_ACTION_DOWN_RUN);
		moveX = 0;
		moveY = -1;
		break;
	default:
		break;
	}
}

PlayerOverWorld::PlayerOverWorld()
{
	setSprite(SpriteManager::getInstance()->getSprite(SPRITE_INFO_PLAYER_ONE_WORLD));
	setWidth(17);
	setHeight(30);
	shootDelay.init(300);
	blinkDelay.init(200);
}


PlayerOverWorld::~PlayerOverWorld()
{
}
