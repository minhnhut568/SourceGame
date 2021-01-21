#include "WorldEnd.h"
#include "SpriteManager.h"
#include "Sound.h"

WorldEnd::WorldEnd()
{
	first = new GameTexture();
	last = new GameTexture();
	first->Init("assets/levels/end/first-scene.png");
	last->Init("assets/levels/end/last-scene.png");
	characterHead = SpriteManager::getInstance()->getSprite(SPRITE_INFO_ENDGAME_HEAD);
	switchSceneDelay.init(1000);
	moveSceneDelay.init(1000);
	state = WORLD_END_STATE_FIRST_SCENE;
	SetRect(&viewport, 0, 0, 258, 224);
	headInterval.init(100);
	current = first;
}

void WorldEnd::start()
{
	switchSceneDelay.start();
}

void WorldEnd::update()
{
	switchSceneDelay.update();
	moveSceneDelay.update();
	if(headInterval.atTime())
	characterHead->update(headAction, headFrame);
	switch (state)
	{
	case WORLD_END_STATE_FIRST_SCENE:
		current = first;
		if (switchSceneDelay.isTerminated())
		{
			state = WORLD_END_STATE_LAST_SCENE;
			moveSceneDelay.start();
		}
		break;
	case WORLD_END_STATE_LAST_SCENE:
		current = last;
		if (moveSceneDelay.isTerminated())
		{
			state = WORLD_END_STATE_RUNNING;
		}
		break;
	case WORLD_END_STATE_RUNNING:
		viewport.left++;
		viewport.right++;
		if (viewport.right + 1 >= last->Width)
		{
			state = WORLD_END_STATE_STOP;
		}
		break;
	case WORLD_END_STATE_STOP:
		break;
	default:
		break;
	}
}

void WorldEnd::render()
{
	current->Render(0, 0, 0, 0, &viewport);
	characterHead->render(407 - viewport.left, 92 - viewport.top, headAction, headFrame);
}
