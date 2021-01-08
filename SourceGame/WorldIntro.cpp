#include "WorldIntro.h"
#include"Game.h"
#include"KEY.h"
#include"World.h"
#include<string>
using namespace std;

WorldIntro::WorldIntro()
{
	introImage = new GameTexture();
	introImage->Init("assets/levels/intro/intro.png");

	introFrameIndex = 0;
	introAction = 0;
	introSprite = SpriteManager::getSprite(SPRITE_INFO_INTRO);
	introTime.init(200);
	introDelay.init(3000);
	GameDirectX::getInstance()->backbufferWidth = 256;
	GameDirectX::getInstance()->backbufferHeight = 224;
}

void WorldIntro::update()
{
	introDelay.update();
	if (introDelay.isTerminated() && introAction < introSprite->animations.Count)
	{
		introAction++;
		introFrameIndex = 0;
	}
	if (!introDelay.isOnTime() && introAction < introSprite->animations.Count)
	{
		if (introTime.atTime())
		{
			introSprite->update(introAction, introFrameIndex);
			if (introFrameIndex == introSprite->animations.at(introAction)->frames.Count - 1)
			{
				introDelay.start();
			}
		}
	}

	TRACE_VAL_LN("introAction", introAction);
	TRACE_VAL_LN("introFrameIndex", introFrameIndex);

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
	SetRect(&r, 0, 0, GameDirectX::getInstance()->backbufferWidth, GameDirectX::getInstance()->backbufferHeight);
	if (introAction == introSprite->animations.Count)
	{
		GameDirectX::getInstance()->backbufferWidth = 256;
		GameDirectX::getInstance()->backbufferHeight = 280;
		introImage->Render(0, 0, 0, 0, 0);
	}
	else
	{
		auto r = introSprite->animations.at(introAction)->frames.at(introFrameIndex);
		introSprite->render(0, 0, introAction, introFrameIndex);
	}


}
