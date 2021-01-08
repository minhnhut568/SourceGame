#pragma once
#include"Sprite.h"
#include"DelayTime.h"
#include"GameTime.h"
class WorldIntro
{
private:
	GameTexture* introImage;
	Sprite* introSprite;
	int introFrameIndex;
	int introAction;

	DelayTime introDelay;
	GameTime introTime;
public:
	WorldIntro();
	void update();
	void render();
};
