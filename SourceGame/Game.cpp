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

	Camera::getInstance()->setSize(
		/* kích thước của camera bằng với kích thước của backbuffer */
		GLOBALS_D("backbuffer_width"),
		GLOBALS_D("backbuffer_height"));
}
/* Các câu lệnh cập nhật game */
void Game::GameUpdate(float dt)
{
	/* cập nhật đối tượng trong world */
	world->update(dt);

	AriseBase::updateAriseObjects(dt);
}
/* Các câu lệnh vẽ của game */
void Game::GameRender()
{
	/* vẽ đối tượng trong world */
	world->render();
}

Game::Game()
{

}


Game::~Game()
{
}
