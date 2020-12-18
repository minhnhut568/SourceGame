#include "PlayerOneWorld.h"
#include "PlayerMiniOverWorldBullet.h"
#include<string>


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
	bool keyLeftDown, keyRightDown, keyUpDown, keyDownDown;
	/* kiểm tra key bên trái có được giữ */
	keyLeftDown = KEY::getInstance()->isLeftDown;
	/* kiểm tra key bên phải có được giữ */
	keyRightDown = KEY::getInstance()->isRightDown;
	keyUpDown = KEY::getInstance()->isUpDown;
	keyDownDown = KEY::getInstance()->isDownDown;

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

	if (KEY::getInstance()->isAttackDown)
	{

	}
}

void PlayerOverWorld::onCollision(MovableRect * other, float collisionTime, int nx, int ny)
{
	if (other->getCollisionType() == COLLISION_TYPE_GROUND)
	{
		/* ngăn chặn di chuyển */
		preventMovementWhenCollision(collisionTime, nx, ny);
		PhysicsObject::onCollision(other, collisionTime, nx, ny);
	}
}

void PlayerOverWorld::onAABBCheck(MovableRect* other)
{
	
}

void PlayerOverWorld::setPlayerDirection(PLAYER_OW_DIRECTION direction)
{
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
}


PlayerOverWorld::~PlayerOverWorld()
{
}
