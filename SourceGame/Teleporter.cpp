#include "Teleporter.h"
#include "PlayerOverWorld.h"


Teleporter::Teleporter()
{
	int change = 30;
	positions = new POINT[8];
	positions[0].x = 0;
	positions[0].y = change;
	
	positions[1].x = -change;
	positions[1].y = 0;

	positions[2].x = 0;
	positions[2].y = -change;

	positions[3].x = 0;
	positions[3].y = -change;

	positions[4].x = change;
	positions[4].y = 0;

	positions[5].x = change;
	positions[5].y = 0;

	positions[6].x = 0;
	positions[6].y = change;

	positions[7].x = 0;
	positions[7].y = change;

	positions[8].x = -change;
	positions[8].y = 0;

	positionIndex = 0;
	moveTime.init(100);
	standDelay.init(200);
}

void Teleporter::onUpdate(float dt)
{
	standDelay.update();
	switch (state)
	{
	case TELEPORTER_STATE_STAND:
		setAnimation(TELEPORTER_ACTION_WEAR);
		if (!standDelay.isOnTime() && abs(getX() - PlayerOverWorld::getInstance()->getX()) < S("teleporter_to_player_distance"))
		{
			state = TELEPORTER_STATE_MOVE;
		}

		break;
	case TELEPORTER_STATE_MOVE:
		setAnimation(TELEPORTER_ACTION_UNWEAR);
		if (moveTime.atTime()) 
		{
			setX(positions[positionIndex].x + getX());
			setY(positions[positionIndex].y + getY());
			positionIndex++;
			if (positionIndex == 9) {
				positionIndex = 1;
			}
		}
		break;
	default:
		break;
	}
}

void Teleporter::onCollision(MovableRect* other, float collisionTime, int nx, int ny)
{
}
