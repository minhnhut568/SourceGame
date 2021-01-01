#include "Boss.h"
#include"Camera.h"
Boss::Boss()
{
	bossAtiveHeight = 100;
	dirX = 1;
	dirY = -1;
	setDx(dirX);
	setDy(dirY);
	runCount = 3;
	isStop = 0;
	delta = 20;
}

double Boss::distanceTwoObj(BaseObject* obj1, BaseObject* obj2)
{
	int dx = obj1->getX() - obj2->getX();
	int dy = obj1->getY() - obj2->getY();
	return sqrt(dx * dx + dy * dy);
}

void Boss::onInitFromFile(ifstream& fs, int mapHeight)
{
	Enemy::onInitFromFile(fs, mapHeight);
	initClaw();
}

void Boss::initClaw()
{
	leftWaveObjects = new List<BaseObject*>();
	leftWaveObjectsRevert = new List<BaseObject*>();
	rightWaveObjects = new List<BaseObject*>();
	leftWaveObjects->_Add(this);
	rightWaveObjects->_Add(this);
	int clawNodeCount = 5;
	bossClawLeft = new BossClaw();
	bossClawLeft->setDirection(-1);
	bossClawLeft->setAnimation(1);
	bossClawLeft->boss = this;
	bossClawLeft->setX(getX());
	bossClawLeft->setY(getY());
	bossClawRight = new BossClaw();
	bossClawRight->setDirection(1);
	bossClawRight->setAnimation(1);
	bossClawRight->boss = this;
	bossClawRight->setX(getRight() + 20);
	bossClawRight->setY(getY());

	for (size_t i = 0; i < clawNodeCount; i++)
	{
		auto bossClawNodeLeft = new BossClaw();
		auto bossClawNodeRight = new BossClaw();

		bossClawNodeLeft->boss = this;
		bossClawNodeRight->boss = this;

		bossClawNodeLeft->setX(getX());
		bossClawNodeLeft->setY(getY());

		bossClawNodeRight->setX(getRight() + 20);
		bossClawNodeRight->setY(getY());

		bossClawNodesLeft._Add(bossClawNodeLeft);
		bossClawNodesRight._Add(bossClawNodeRight);

		leftWaveObjects->_Add(bossClawNodeLeft);
		rightWaveObjects->_Add(bossClawNodeRight);
	}

	leftWaveObjects->_Add(bossClawLeft);
	rightWaveObjects->_Add(bossClawRight);

	for (int i = leftWaveObjects->Count - 1; i > 0; i--)
	{
		leftWaveObjectsRevert->_Add(leftWaveObjects->at(i));
	}
}

void Boss::runWave(List<BaseObject*>* objects)
{
	for (int i = 1; i < objects->Count; i++)
	{
		auto curObj = objects->at(i - 1);
		auto preObj = objects->at(i);

		auto distance = distanceTwoObj(preObj, curObj);
		if (distance > delta)
		{
			float x1 = curObj->getX() - preObj->getX();
			float y1 = curObj->getY() - preObj->getY();

			float x12 = x1 * x1;
			float y12 = y1 * y1;

			float y0 = 0;
			float x0 = 0;
			if (abs(y1) == 0)
			{
				x0 = delta;
			}
			else
			{
				y0 = sqrt((delta * delta) / ((x12 / y12) + 1));
				x0 = sqrt((delta * delta) / ((y12 / x12) + 1));
			}

			if (curObj->getY() > preObj->getY())
			{
				y0 = -y0;
			}

			if (curObj->getX() > preObj->getX())
			{
				x0 = -x0;
			}

			preObj->setX((int)(curObj->getX() + x0));
			preObj->setY((int)(curObj->getY() + y0));
		}

	}
}

void Boss::onUpdate(float dt)
{
	leftWaveObjectsRevert->at(0)->setDy(3);
	runWave(leftWaveObjectsRevert);
	runWave(leftWaveObjects);
	//runWave(rightWaveObjects);
	auto camera = Camera::getInstance();
	auto dy = dirY;
	auto dx = dirX;
	auto y = getY();
	auto x = getX();

	auto nextY = y + dy;


	if ((dy < 0 && nextY < camera->getY() - bossAtiveHeight) || (dy > 0 && nextY > camera->getY()))
	{
		dirY = -dirY;
	}

	if ((dx < 0 && x + dx < camera->getX()) || (dx > 0 && getRight() + dx > camera->getRight()))
	{
		dirX = -dirX;
	}

	if (isStop == 0)
	{
		setDx(dirX);
		setDy(dirY);
	}
	else
	{
		setDx(0);
		setDy(0);
	}
	isStop = (isStop + 1) % runCount;

}