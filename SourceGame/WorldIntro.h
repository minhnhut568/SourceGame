#pragma once
#include"Sprite.h"
#include"DelayTime.h"
#include"GameTime.h"
class WorldIntro
{
private:
	GameTexture* introImage;
	Sprite* introStory;
	Sprite* introCar;
	Sprite* introTitle;
	int introFrameIndex;
	int introAction;
	int i;
	RECT r;

	DelayTime introDelay;
	GameTime introTime;
public:
	WorldIntro();
	void IntroTime(Sprite *abc);
	void update();
	void render();
};
