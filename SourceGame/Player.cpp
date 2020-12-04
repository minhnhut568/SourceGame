#include "Player.h"
#include "PlayerBullet.h"
#include"PlayerMini.h"
#include<string>

PhysicsObject* Player::instance = 0;


PhysicsObject* Player::playerMain = 0;
PhysicsObject* Player::playerMini = 0;
PhysicsObject* Player::currentPlayer = 0;

PhysicsObject* Player::getPlayerMain()
{
	if (playerMain == 0)
	{
		playerMain = new Player();
	}
	return playerMain;
}

PhysicsObject* Player::getPlayerMini()
{
	if (playerMini == 0)
	{
		playerMini = new PlayerMini();
	}
	return playerMini;
}

void Player::changeToPlayerMini()
{
	playerMain->setVx(0);
	playerMain->setVy(0);
	playerMain->setDx(0);
	playerMain->setDy(0);
	playerMain->setAnimation(PLAYER_ACTION_STAND);
	playerMini->setX(playerMain->getMidX());
	playerMini->setY(playerMain->getY());
	currentPlayer = getPlayerMini();
}
void Player::changeToPlayerMain()
{
	currentPlayer = getPlayerMain();
}
PhysicsObject* Player::getInstance()
{
	return currentPlayer;
}

void Player::onUpdate(float dt)
{
	if (currentPlayer == playerMini)
	{
		PhysicsObject::onUpdate(dt);
		return;
	}
	bulletDelay.update();
	bool keyLeftDown, keyRightDown, keyUpDown, keyDownDown, keyJumpPress, changePlayerDown;
	/* kiểm tra key bên trái có được giữ */
	keyLeftDown = KEY::getInstance()->isLeftDown;
	/* kiểm tra key bên phải có được giữ */
	keyRightDown = KEY::getInstance()->isRightDown;
	keyUpDown = KEY::getInstance()->isUpDown;
	keyDownDown = KEY::getInstance()->isDownDown;

	/* kiểm tra key jump có được nhấn */
	keyJumpPress = KEY::getInstance()->isJumpPress;
	changePlayerDown = KEY::getInstance()->changePlayer;

	if (changePlayerDown)
	{
		Player::changeToPlayerMini();
	}

	float vx = GLOBALS_D("player_vx");

	int animation = getAnimation();
	int frame = getFrameAnimation();
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

	/* nếu vật đứng trên sàn */
	if (getIsOnGround())
	{
		// nếu nhấn key lên
		if (keyUpDown)
		{
			if (animation != PLAYER_ACTION_SHOOT_UP)
			{
				setAnimation(PLAYER_ACTION_SHOOTING_UP);
				if (animation == PLAYER_ACTION_SHOOTING_DOWN || animation == PLAYER_ACTION_SHOOTING_UP)
				{
					setFrameAnimation(frame);
				}
			}
			if (getIsLastFrameAnimationDone())
			{
				setAnimation(PLAYER_ACTION_SHOOT_UP);
			}
		}
		else
		{

			if ((animation == PLAYER_ACTION_SHOOT_UP) || (animation == PLAYER_ACTION_SHOOTING_UP))
			{
				setAnimation(PLAYER_ACTION_SHOOTING_DOWN);
				if (animation == PLAYER_ACTION_SHOOTING_DOWN || animation == PLAYER_ACTION_SHOOTING_UP)
				{
					setFrameAnimation(frame);
				}
			}
			else if (animation != PLAYER_ACTION_SHOOTING_DOWN || (animation == PLAYER_ACTION_SHOOTING_DOWN && getIsLastFrameAnimationDone()))
			{
				if (getVx() == 0)
				{
					setPauseAnimation(false);
					setAnimation(PLAYER_ACTION_STAND);
				}
				else
				{
					setPauseAnimation(true);
					setAnimation(PLAYER_ACTION_RUN);
				}
			}
			/* set animation đứng yên */
		}

		/* nếu đứng trên sàn mà nhấn key jump thì sẽ cho nhân vật nhảy. còn nếu ở trên không mà nhấn key jump thì nó sẽ
		không vào chỗ này vì không thỏa mãn isOnGround = true*/
		if (keyJumpPress)
		{
			setVy(GLOBALS_D("player_vy_jump"));
		}
	}
	else /* nếu nhân vật không đứng trên sàn (đang lơ lững trên không) */
	{
		if (getVy() > 0)
		{
			setAnimation(PLAYER_ACTION_JUMP);
			if (getFrameAnimation() == getLastFrameCurrentAnimation())
			{
				setPauseAnimation(true);
			}
		}
		else
		{
			setPauseAnimation(false);
			setAnimation(PLAYER_ACTION_JUMP_DOWN);
		}
	}

	if (KEY::getInstance()->isAttackDown && !bulletDelay.isOnTime())
	{
		PlayerBullet* bullet = new PlayerBullet();
		bullet->setX(getMidX());
		bullet->setY(getY());
		bullet->setDirection(getDirection());
		if (keyUpDown)
		{
			bullet->setDx(0);
			bullet->setDy(S("playerbullet_dx"));
			bullet->setAnimation(BULLET_ANIMATION_VER);
		}
		else
		{
			bullet->setDx(getDirection() * S("playerbullet_dx"));
			bullet->setDy(0);
			bullet->setAnimation(BULLET_ANIMATION_HOR);
		}
		bulletDelay.start();
	}

	/* gọi lại phương thức xử lý onUpdate đã được định nghĩa ở lớp cha control click vào PhysicsObject::onUpdate để biết */

	PhysicsObject::onUpdate(dt);
}

void Player::onCollision(MovableRect * other, float collisionTime, int nx, int ny)
{
	if (other->getCollisionType() == COLLISION_TYPE_GROUND)
	{
		/* ngăn chặn di chuyển */
		preventMovementWhenCollision(collisionTime, nx, ny);
		PhysicsObject::onCollision(other, collisionTime, nx, ny);
	}
}

void Player::updatePlayer(float dt)
{
	if (currentPlayer == playerMini)
	{
		playerMain->update(dt);
		playerMini->update(dt);
	}
	else
	{
		playerMain->update(dt);
	}
}

void Player::renderPlayer()
{
	if (currentPlayer == playerMini)
	{
		playerMain->render(Camera::getInstance());
		playerMini->render(Camera::getInstance());
	}
	else
	{
		playerMain->render(Camera::getInstance());
	}
}

Player::Player()
{
	setSprite(SPR(SPRITE_INFO_PLAYER));
	bulletDelay.init(S("player_bulle_delay"));
	setDirection(TEXTURE_DIRECTION::TEXTURE_DIRECTION_RIGHT);
}


Player::~Player()
{
}
