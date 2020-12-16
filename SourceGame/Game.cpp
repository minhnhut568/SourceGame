#include "Game.h"
#include "AriseBase.h"
#include"Player.h"

/* singleton pattern */
Game* Game::instance = 0;
Game* Game::getInstance()
{
	if (instance == 0)
		instance = new Game();
	return instance;
}

/* Các câu lệnh khởi tạo game */
void Game::GameInit()
{
	/* khởi tạo tilemap */
	world = new World();
	world->Init("assets/levels/area2");

	oneWorld = new OneWorld();
	oneWorld->Init("assets/levels/area2_oneworld");

	worldIntro = new WorldIntro();

	Camera::getInstance()->setSize(
		/* kích thước của camera bằng với kích thước của backbuffer */
		GLOBALS_D("backbuffer_width"),
		GLOBALS_D("backbuffer_height"));

	worldType = WT_WORLD;

	world->setCurrentSpace(0);
	world->resetLocationInSpace();

	// GameDirectX::getInstance()->initDirectXWithSize(256, 280);
}
/* Các câu lệnh cập nhật game */
void Game::GameUpdate(float dt)
{
	switch (worldType)
	{
	case WT_INTRO:
		worldIntro->update();
		break;
	case WT_WORLD:
		world->update(dt);
		break;
	case WT_ONE_WORLD:
		oneWorld->update(dt);
		break;
	default:
		break;
	}

	AriseBase::updateAriseObjects(dt);
}
/* Các câu lệnh vẽ của game */
void Game::GameRender()
{
	switch (worldType)
	{
	case WT_INTRO:
		worldIntro->render();
		break;
	case WT_WORLD:
		world->render();
		break;
	case WT_ONE_WORLD:
		oneWorld->render();
		break;
	default:
		break;
	}
}

Game::Game()
{

}


Game::~Game()
{
}
