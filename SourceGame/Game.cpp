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

	overWorld = new OverWorld();
	overWorld->Init("assets/levels/area2_oneworld");

	worldIntro = new WorldIntro();

	Camera::getInstance()->setSize(
		/* kích thước của camera bằng với kích thước của backbuffer */
		GLOBALS_D("backbuffer_width"),
		GLOBALS_D("backbuffer_height"));


	// world
	/*worldType = WT_WORLD;
	world->setCurrentSpace(4);
	world->resetLocationInSpace();*/

	// over world
	worldType = WT_OVER_WORLD_SPACE0;
	overWorld->setCurrentSpace(2);
	overWorld->resetLocationInSpace();

	// intro
	/*worldType = WT_INTRO;*/
//<<<<<<< Updated upstream
//=======
//
//
//>>>>>>> Stashed changes
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
	case WT_OVER_WORLD_SPACE0:
		overWorld->update(dt);
		break;
	case WT_OVER_WORLD_SPACE1:
		overWorld->update(dt);
		break;
	case WT_OVER_WORLD_SPACE2:
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
	case WT_OVER_WORLD_SPACE0:
		overWorld->render();
		Scorebar::getInstance()->render();
		break;
	case WT_OVER_WORLD_SPACE1:
		overWorld->render();
		Scorebar::getInstance()->render();
		break;
	case WT_OVER_WORLD_SPACE2:
		overWorld->render();
		Scorebar::getInstance()->render();
		break;
	default:
		break;
	}
}

WorldType Game::getWorldType()
{
	return worldType;
}

void Game::setWorldType(WorldType worldType)
{
	auto gameDirectx = GameDirectX::getInstance();
	this->worldType = worldType;
	switch (worldType)
	{
	case WT_INTRO:
		gameDirectx->backbufferWidth = 256;
		gameDirectx->backbufferHeight = 280;
		break;
	case WT_WORLD:
		gameDirectx->backbufferWidth = 240;
		gameDirectx->backbufferHeight = 224;
		break;
	case WT_OVER_WORLD_SPACE0:
	case WT_OVER_WORLD_SPACE1:
	case WT_OVER_WORLD_SPACE2:
	case WT_TO_WORLD_SPACE6:
	case WT_TO_WORLD_SPACE4:
	case WT_TO_WORLD_SPACE5:
		gameDirectx->backbufferWidth = 256;
		gameDirectx->backbufferHeight = 224;
	default:
		break;
	}


	Camera::getInstance()->setWidth(gameDirectx->backbufferWidth);
	Camera::getInstance()->setHeight(gameDirectx->backbufferHeight);
}

Game::Game()
{

}


Game::~Game()
{
}
