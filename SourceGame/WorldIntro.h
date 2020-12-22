#pragma once
#include"GameTexture.h"
class WorldIntro
{
	GameTexture* introImage;
public:
	WorldIntro();
	void update();
	void render();
};
