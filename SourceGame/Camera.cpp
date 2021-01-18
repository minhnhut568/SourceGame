#include "Camera.h"
#include<d3dx9.h>
#include"Player.h"
#include"PlayerOverWorld.h"
#include"Game.h"
#include"CollisionType.h"

Camera* Camera::instance = 0;
void Camera::removeObject(BaseObject* obj)
{
	allObjects->_Remove(obj);
	objectCategories.at(obj->getCollisionType())->_Remove(obj);
}
Camera* Camera::getInstance()
{
	if (instance == 0)
	{
		instance = new Camera();
	}
	return instance;
}

void Camera::convertWorldToView(float xWorld, float yWorld, float& xView, float& yView)
{
	/* ma trận biến đổi world to view */
	D3DXMATRIX matrixWorldToView;
	D3DXMatrixIdentity(&matrixWorldToView);
	matrixWorldToView._22 = -1;
	matrixWorldToView._41 = -this->getX();
	matrixWorldToView._42 = this->getY();

	/* nhân ma trận đó với xWorld yWorld ta được xView yView */
	D3DXVECTOR3 pos3(xWorld, yWorld, 1);
	D3DXVECTOR4 MatrixResult;
	D3DXVec3Transform(&MatrixResult, &pos3, &matrixWorldToView);

	xView = MatrixResult.x;
	yView = MatrixResult.y;


}

void Camera::onCollision(MovableRect* other, float collisionTime, int nx, int ny)
{
	preventMovementWhenCollision(collisionTime, nx, ny);
}

void Camera::setSpace(Space* space)
{
	this->space = space;
}

void Camera::update()
{
	/* mặc định cho camera đứng yên, chỉ khi player chạy nó mới chạy theo */
	setDx(0);

	BaseObject* player = 0;
	switch (Game::getInstance()->getWorldType())
	{
	case WT_OVER_WORLD_SPACE0:
		player = PlayerOverWorld::getInstance();
		break;
	case WT_OVER_WORLD_SPACE1:
		player = PlayerOverWorld::getInstance();
		break;
	case WT_OVER_WORLD_SPACE2:
		player = PlayerOverWorld::getInstance();
		break;
	case WT_WORLD:
		player = Player::getInstance();
		break;
	case WT_END:
		return;
	default:
		break;
	}

	/* nếu player đang chạy sang trái (player->getDx()<0) và phần giữa camera nằm bên phải phần giữa player */
	if (player->getDx() < 0 && getMidX() > player->getMidX())
	{
		/* thì cho camera chạy theo player (về bên trái) */
		setDx(player->getDx());
	}
	/* nếu player đang chạy sang phải (player->getDx()>0) và phần giữa camera nằm bên trái phần giữa player */
	if (player->getDx() > 0 && getMidX() < player->getMidX())
	{
		/* thì cho camera chạy theo player (về bên phải) */
		setDx(player->getDx());
	}

	/* nếu camera chạy sang trái và vượt quá góc trái space  */
	if (getX() + getDx() < space->X && getDx() < 0)
	{
		setX(space->X);
		setDx(0);
	}

	/* nếu camera chạy sang phải và vượt quá góc phải space  */
	if (getRight() + getDx() > space->X + space->Width && getDx() > 0)
	{
		setX(space->X + space->Width - getWidth());
		setDx(0);
	}

	/* nếu player chạy sang trái và vượt quá góc trái space  */
	if (player->getX() + player->getDx() < space->X && player->getDx() < 0)
	{
		player->setX(space->X);
		player->setDx(0);
	}

	/* nếu player chạy sang phải và vượt quá góc phải space  */
	if (player->getRight() + player->getDx() > space->X + space->Width && player->getDx() > 0)
	{
		player->setX(space->X + space->Width - player->getWidth());
		player->setDx(0);
	}

	// y

	if (player->getDy() < 0 && getMidY() > player->getMidY())
	{

		setDy(player->getDy());
	}
	else if (player->getDy() > 0 && getMidY() < player->getMidY())
	{

		setDy(player->getDy());
	}
	else
	{
		setDy(0);
	}


	if (getBottom() + getDy() < space->Y - space->Height && getDy() < 0)
	{
		setY(space->Y - space->Height + getHeight());
		setDy(0);
	}


	if (getTop() + getDy() > space->Y && getDy() > 0)
	{
		setY(space->Y);
		setDy(0);
	}


	goX();
	goY();
}

Camera::Camera()
{
	alive = true;
	allObjects = new List<BaseObject*>();
	for (size_t i = 0; i < COLLISION_TYPE_COUNT; i++)
	{
		objectCategories._Add(new List<BaseObject*>());
	}
}


Camera::~Camera()
{
}
