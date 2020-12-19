#include "Game.h"
#include "AriseBase.h"
#include"Player.h"
#include"Scorebar.h"

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

	overWorld = new OneWorld();
	overWorld->Init("assets/levels/area2_oneworld");

	worldIntro = new WorldIntro();

	Camera::getInstance()->setSize(
		/* kích thước của camera bằng với kích thước của backbuffer */
		GLOBALS_D("backbuffer_width"),
		GLOBALS_D("backbuffer_height"));

	worldType = WT_WORLD;



	world->setCurrentSpace(5);
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
	case WT_OVER_WORLD:
		overWorld->update(dt);
		break;
	default:
		break;
	}

	AriseBase::updateAriseObjects(dt);
	Scorebar::getInstance()->update();
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
		Scorebar::getInstance()->render();
		break;
	case WT_OVER_WORLD:
		overWorld->render();
		Scorebar::getInstance()->render();
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
