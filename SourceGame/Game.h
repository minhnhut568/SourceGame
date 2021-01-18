#pragma once
#include"GameTexture.h"
#include"List.h"
#include"GameTime.h"
#include"FrameAnimation.h"
#include"Animation.h"
#include"Sprite.h"
#include"World.h"
#include"OverWorld.h"
#include "WorldIntro.h"
#include "WorldEnd.h"

enum WorldType
{
	WT_INTRO,
	WT_WORLD,
	WT_OVER_WORLD_SPACE0,
	WT_OVER_WORLD_SPACE1,
	WT_OVER_WORLD_SPACE2,
	WT_TO_WORLD_SPACE6,
	WT_TO_WORLD_SPACE4,
	WT_TO_WORLD_SPACE5,
	WT_END
};

class Game
{
private:
	/* singleton pattern */
	static Game* instance;
	WorldType worldType;


public:
	World* world;

	OverWorld* overWorld;
	WorldIntro* worldIntro;
	WorldEnd* worldEnd;
	static Game* getInstance();
	/* Các câu lệnh khởi tạo game */
	void GameInit();
	/* Các câu lệnh cập nhật game */
	void GameUpdate(float dt);
	/* Các câu lệnh vẽ của game */
	void GameRender();
	WorldType getWorldType();

	void setWorldType(WorldType worldType);
	Game();
	~Game();
};

