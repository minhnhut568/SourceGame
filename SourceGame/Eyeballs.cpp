#include "Eyeballs.h"
#include "PlayerOverWorld.h"
#include "FloaterBullet.h"
#include "Sound.h"
//random lib
#include <cstdlib>
#include <ctime>


Eyeballs::Eyeballs()
{
	//move //dont finish
	int change[4];
	for (int i = 0; i < 4; i++) {
		srand(time(NULL));
		change[i] = rand() % (10 + 10 + 1) - 10;
	}

	positions = new POINT[4];

	positions[0].x = 0;
	positions[0].y = change[0];

	positions[1].x = change[1];
	positions[1].y = 0;

	positions[2].x = 0;
	positions[2].y = change[2];

	positions[3].x = change[3];
	positions[3].y = 0;

	positionIndex = 0; //num in array

	eyeballsState = EYEBALLS_STATE_MOVE;
	runDelay.start();
	moveTime.init(500);
	standDelay.init(2000);
}

void Eyeballs::onUpdate(float dt)
{
	standDelay.update();
	switch (eyeballsState) {
	case EYEBALLS_STATE_STAND:
		if (!standDelay.isOnTime() && abs(getX() - PlayerOverWorld::getInstance()->getX()) < S("teleporter_to_player_distance")) {

			eyeballsState = EYEBALLS_STATE_MOVE;
		}
		break;
	case EYEBALLS_STATE_MOVE:
		if (moveTime.atTime()) {
			//wallet shoot follow direct Player
			FloaterBullet* bullet = new FloaterBullet();
			bullet->setX(this->getMidX());
			bullet->setY(this->getMidY());

			auto player = PlayerOverWorld::getInstance();

			auto xb = bullet->getX();
			auto yb = bullet->getY();
			auto xp = player->getX();
			auto yp = player->getY();
			auto r = S("floater_r");

			if (abs(yp - yb) <= 20)
			{
				if (getMidX() < player->getMidX())
				{
					bullet->setDx(r);
				}
				else
				{
					bullet->setDx(-r);
				}
			}
			else
			{
				auto m = ((xp - xb) * (xp - xb)) / ((yp - yb) * (yp - yb));

				auto dx = sqrt(r * r * m / (1 + m));

				if (getMidX() < player->getMidX())
				{
					bullet->setDx(dx);
				}
				else
				{
					bullet->setDx(-dx);
				}

				auto dy = sqrt(abs(r * r - dx * dx));

				if (getMidY() < player->getMidY())
				{
					bullet->setDy(dy);
				}
				else
				{
					bullet->setDy(-dy);
				}
			}
			auto xx = bullet->getDx();
			auto yy = bullet->getDy();
			TRACE_VAL_LN("dx", xx);
			TRACE_VAL_LN("dy", yy);

			setX(positions[positionIndex].x + getX());
			setY(positions[positionIndex].y + getY());
			positionIndex++;
			if (positionIndex == 4) {
				positionIndex = 1;
			}

			eyeballsState = EYEBALLS_STATE_STAND;
			standDelay.start();

		}
		break;
	}
}

void Eyeballs::onCollision(MovableRect* other, float collisionTime, int nx, int ny)
{
}
