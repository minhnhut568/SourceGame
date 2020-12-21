#include "WorldIntro.h"
#include"Game.h"
#include"KEY.h"
#include"World.h"

WorldIntro::WorldIntro()
{
	introImage = new GameTexture();
	introImage->Init("assets/levels/intro/intro.png");
}

void WorldIntro::update()
{
	KEY::getInstance()->update();
	if (KEY::getInstance()->isEnterDown)
	{
		Game::getInstance()->setWorldType(WorldType::WT_WORLD);
		Game::getInstance()->world->setCurrentSpace(0);
		Game::getInstance()->world->resetLocationInSpace();
	}
}

void WorldIntro::render()
{
	RECT r;
	introImage->Render(0, 0, 0, 0, 0);
}
