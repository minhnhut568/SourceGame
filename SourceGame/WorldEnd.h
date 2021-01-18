#pragma once
#include"Sprite.h"
#include"DelayTime.h"
#include"GameTime.h"

enum WORLD_END_STATE {
	WORLD_END_STATE_FIRST_SCENE,
	WORLD_END_STATE_LAST_SCENE,
	WORLD_END_STATE_RUNNING,
	WORLD_END_STATE_STOP
};
class WorldEnd
{
private:
	GameTexture* current, *first, *last;
	Sprite* characterHead;
	DelayTime switchSceneDelay, moveSceneDelay;
	WORLD_END_STATE state;
	RECT viewport;
	int headAction, headFrame;

	GameTime headInterval;

public:
	WorldEnd();
	void start();
	void update();
	void render();
};