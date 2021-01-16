#include "WorldIntro.h"
#include"Game.h"
#include"KEY.h"
#include"World.h"
#include"Sound.h"

#include<string>
using namespace std;

WorldIntro::WorldIntro()
{
	introImage = new GameTexture();
	introImage->Init("assets/levels/intro/intro.png");
	introFrameIndex = 0;
	introAction = 0;
	i = 1;
	introStory = SpriteManager::getSprite(SPRITE_INFO_INTRO_STORY);
	introCar = SpriteManager::getSprite(SPRITE_INFO_INTRO_CAR);
	introTitle = SpriteManager::getSprite(SPRITE_INFO_INTRO_TITLE);
	GameDirectX::getInstance()->backbufferWidth = 256;
	GameDirectX::getInstance()->backbufferHeight = 280;
}

void WorldIntro::IntroTime(Sprite *temp)
{
	introDelay.update();
	if (introDelay.isTerminated() && introAction < temp->animations.Count)
	{
		introAction++;
		introFrameIndex = 0;
	}
	if (!introDelay.isOnTime() && introAction < temp->animations.Count)
	{
		if (introTime.atTime())
		{
			temp->update(introAction, introFrameIndex);
			if (introFrameIndex == temp->animations.at(introAction)->frames.Count - 1)
			{
				introDelay.start();
			}
		}
	}
	if (introAction == temp->animations.Count)
	{
		i++;
		introFrameIndex = 0;
		introAction = 0;
		if (i == 2)
		{
			GameDirectX::getInstance()->backbufferHeight = 224;
		}
		if (i == 4)
		{
			GameDirectX::getInstance()->backbufferHeight = 280;
		}
	}
}

void WorldIntro::update()
{

	switch (i)
	{
	case 1:		
		introTime.init(50);
		introDelay.init(1000);
		IntroTime(introTitle);
		break;
	case 2:
		Sound::getInstance()->play("Intro", true, 0);	
		introTime.init(300);
		introDelay.init(1000);
		IntroTime(introStory);
		break;
	case 3:
		Sound::getInstance()->stop("Intro");
		Sound::getInstance()->play("CarBackground", true, 0);
		introTime.init(100);
		introDelay.init(500);
		IntroTime(introCar);
		break;
	case 4:
		Sound::getInstance()->stop("CarBackground");
		Sound::getInstance()->stop("CarSplash");
		introTime.init(50);
		introDelay.init(1000);
		IntroTime(introTitle);
		break;
	case 5:
		Game::getInstance()->setWorldType(WorldType::WT_WORLD);
		Game::getInstance()->world->setCurrentSpace(0);
		Game::getInstance()->world->resetLocationInSpace();
	default:
		break;
	}
	

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
	if (i == 1)
	{
		SetRect(&r, 0, 0, GameDirectX::getInstance()->backbufferWidth, GameDirectX::getInstance()->backbufferHeight);
		auto r = introTitle->animations.at(introAction)->frames.at(introFrameIndex);
		introTitle->render(0, 0, introAction, introFrameIndex);
	}
	if (i == 2)
	{
		SetRect(&r, 0, 0, GameDirectX::getInstance()->backbufferWidth, GameDirectX::getInstance()->backbufferHeight);
		auto r = introStory->animations.at(introAction)->frames.at(introFrameIndex);
		introStory->render(0, 0, introAction, introFrameIndex);
	}
	if (i == 3)
	{
		SetRect(&r, 0, 0, GameDirectX::getInstance()->backbufferWidth, GameDirectX::getInstance()->backbufferHeight);
		auto g = introCar->animations.at(introAction)->frames.at(introFrameIndex);
		if (introAction == 1)
		{
			Sound::getInstance()->play("CarSplash", true, 0);
		}
		introCar->render(0, 0, introAction, introFrameIndex);
	}
	if (i == 4)
	{
		SetRect(&r, 0, 0, GameDirectX::getInstance()->backbufferWidth, GameDirectX::getInstance()->backbufferHeight);
		auto r = introTitle->animations.at(introAction)->frames.at(introFrameIndex);
		introTitle->render(0, 0, introAction, introFrameIndex);
	}
}
