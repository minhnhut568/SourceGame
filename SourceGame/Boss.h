#pragma once
#include "Enemy.h"
#include"BossClaw.h"
#include"DelayTime.h"
#include "GameTime.h"
#include"Sound.h"
class Boss :
	public Enemy
{
	int bossAtiveHeight;
	int dirX, dirY;
	int isStop;
	int runCount;
	DelayTime delayBullet;
	GameTime shootTime;

	int delta;
	int health;
	static Boss* instance;
public:
	static Boss* getInstance();
	Boss();
	List<BossClaw*> bossClawNodesLeft;
	BossClaw* bossClawLeft;
	List<BossClaw*> bossClawNodesRight;
	BossClaw* bossClawRight;

	List<BaseObject*>* leftWaveObjects;
	List<BaseObject*>* rightWaveObjects;

	List<BaseObject*>* leftWaveObjectsRevert;
	List<BaseObject*>* rightWaveObjectsRevert;

	GameTime clawDyDelayTime;
	int bossClawDyDirection;

	BaseObject* bossRightArm;

	DelayTime infinityDelay;

	double distanceTwoObj(BaseObject* obj1, BaseObject* obj2);

	void onInitFromFile(ifstream& fs, int mapHeight);

	void initClaw();

	void runWave(List<BaseObject*>* objects);
	
	void onUpdate(float dt) override;

	void setConflicBullet(BaseObject* bullet) override;
};