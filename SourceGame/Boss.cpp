#include "Boss.h"
#include"Camera.h"
#include<time.h>
#include<string>
Boss* Boss::instance = 0;
Boss* Boss::getInstance()
{
	return instance;
}
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
	clawDyDelayTime.init(500);
	bossClawDyDirection = -1;
	bossRightArm = new BaseObject();
	health = 20;

	infinityDelay.init(100);
	infinityDelay.start();
	instance = this;
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
	rightWaveObjectsRevert = new List<BaseObject*>();
	rightWaveObjects = new List<BaseObject*>();
	leftWaveObjects->_Add(this);
	rightWaveObjects->_Add(bossRightArm);
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

	for (int i = rightWaveObjects->Count - 1; i > 0; i--)
	{
		rightWaveObjectsRevert->_Add(rightWaveObjects->at(i));
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
	infinityDelay.update();
	srand(time(NULL));
	bossRightArm->setY(getY());
	bossRightArm->setX(getRight() - 10);
	if (clawDyDelayTime.atTime())
	{
		bossClawDyDirection = -bossClawDyDirection;
	}

	auto sign = (rand() % 2) == 0? 1 : -1;

	leftWaveObjectsRevert->at(0)->setDy(10 * bossClawDyDirection);
	leftWaveObjectsRevert->at(0)->setDx(-sign*rand() % 10 + getDx());
	runWave(leftWaveObjectsRevert);
	runWave(leftWaveObjects);

	rightWaveObjectsRevert->at(0)->setDy(10 * bossClawDyDirection);
	rightWaveObjectsRevert->at(0)->setDx(sign * rand() % 10 + getDx());
	runWave(rightWaveObjectsRevert);
	runWave(rightWaveObjects);
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

void Boss::setConflicBullet(BaseObject* bullet)
{
	Sound::getInstance()->play("BulletTouchBoss", false, 1);
	bullet->alive = false;
	if (infinityDelay.isTerminated())
	{
		health--;
		infinityDelay.start();
	}
	if (health <= 0)
	{
		Sound::getInstance()->play("BossDie", false, 1);
		Enemy::setConflicBullet(bullet);
	}
}
