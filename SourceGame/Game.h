#pragma once
#include"GameTexture.h"
#include"List.h"
#include"GameTime.h"
#include"FrameAnimation.h"
#include"Animation.h"
#include"Sprite.h"
#include"World.h"
#include"OverWorld.h"
#include"WorldIntro.h"

enum WorldType
{
	WT_INTRO,
	WT_WORLD,
	WT_OVER_WORLD
};

class Game
{
	/* singleton pattern */
	static Game* instance;


public:
	World* world;

	OneWorld* overWorld;
	WorldIntro* worldIntro;
	WorldType worldType;
	static Game* getInstance();
	/* Các câu lệnh khởi tạo game */
	void GameInit();
	/* Các câu lệnh cập nhật game */
	void GameUpdate(float dt);
	/* Các câu lệnh vẽ của game */
	void GameRender();
	Game();
	~Game();
};

