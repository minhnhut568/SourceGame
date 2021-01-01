#pragma once
#include "Enemy.h"
#include"BossClaw.h"
class Boss :
	public Enemy
{
	int bossAtiveHeight;
	int dirX, dirY;
	int isStop;
	int runCount;

	int delta;
public:
	Boss();
	List<BossClaw*> bossClawNodesLeft;
	BossClaw* bossClawLeft;
	List<BossClaw*> bossClawNodesRight;
	BossClaw* bossClawRight;

	List<BaseObject*>* leftWaveObjects;
	List<BaseObject*>* rightWaveObjects;

	List<BaseObject*>* leftWaveObjectsRevert;

	double distanceTwoObj(BaseObject* obj1, BaseObject* obj2);

	void onInitFromFile(ifstream& fs, int mapHeight);

	void initClaw();

	void runWave(List<BaseObject*>* objects);
	
	void onUpdate(float dt) override;
};