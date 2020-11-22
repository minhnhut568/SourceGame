#include "Camera.h"
#include<d3dx9.h>
#include"Player.h"

Camera * Camera::instance = 0;
Camera * Camera::getInstance()
{
	if (instance == 0)
	{
		instance = new Camera();
	}
	return instance;
}

void Camera::convertWorldToView(float xWorld, float yWorld, float & xView, float & yView)
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

void Camera::setSpace(Space * space)
{
	this->space = space;
}

void Camera::update()
{
	/* mặc định cho camera đứng yên, chỉ khi player chạy nó mới chạy theo */
	setDx(0);

	Player* player = Player::getInstance();
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

	/* nếu player đang chạy sang trái (player->getDy()<0) và phần giữa camera nằm bên phải phần giữa player */
	if (player->getDy() < 0 && getMidY() > player->getMidY())
	{
		/* thì cho camera chạy theo player (về bên trái) */
		setDy(player->getDy());
	}
	else if (player->getDy() > 0 && getMidY() < player->getMidY())
	{
		/* thì cho camera chạy theo player (về bên phải) */
		setDy(player->getDy());
	}
	else
	{
		setDy(0);
	}

	/* nếu camera chạy sang trái và vượt quá góc trái space  */
	if (getBottom() + getDy() < space->Y - space->Height && getDy() < 0)
	{
		setY(space->Y - space->Height + getHeight());
		setDy(0);
	}

	/* nếu camera chạy sang phải và vượt quá góc phải space  */
	if (getTop() + getDy() > space->Y && getDy() > 0)
	{
		setY(space->Y);
		setDy(0);
	}

	///* nếu player chạy sang trái và vượt quá góc trái space  */
	//if (player->getY() + player->getDy() < space->Y && player->getDy() < 0)
	//{
	//	player->setY(space->Y);
	//	player->setDy(0);
	//}

	///* nếu player chạy sang phải và vượt quá góc phải space  */
	//if (player->getTop() + player->getDy() > space->Y + space->Height && player->getDy() > 0)
	//{
	//	player->setY(space->Y + space->Height - player->getHeight());
	//	player->setDy(0);
	//}

	/* cập nhật vị trí camera */
	goX();
	goY();
}

Camera::Camera()
{
}


Camera::~Camera()
{
}
