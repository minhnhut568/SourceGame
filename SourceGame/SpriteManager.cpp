#include "SpriteManager.h"
SpriteManager * SpriteManager::instance = 0;
SpriteManager * SpriteManager::getInstance()
{
	if (instance == 0)
	{
		instance = new SpriteManager();
	}
	return instance;
}
Sprite * SpriteManager::getSprite(int spriteInfo)
{
	return getInstance()->sprites[spriteInfo];
}
SpriteManager::SpriteManager()
{
	/* thêm SPRITE_COUNT phần tử cho list sprite */
	for (size_t i = 0; i < SPRITE_COUNT; i++)
	{
		sprites._Add(new Sprite());
	}

	

	/* đăng ký sprite cho player */
	sprites[SPRITE_INFO_PLAYER]->InitFromFile("assets/sprites/player");
	sprites[SPRITE_INFO_PLAYER]->image->direction = TEXTURE_DIRECTION_RIGHT;

	// bullet
	sprites[SPRITE_INFO_BULLET]->InitFromFile("assets/sprites/bullet");
	sprites[SPRITE_INFO_BULLET]->image->direction = TEXTURE_DIRECTION_LEFT;

	//worm
	sprites[SPRITE_INFO_WORM]->InitFromFile("assets/sprites/worm");
	sprites[SPRITE_INFO_WORM]->image->direction = TEXTURE_DIRECTION_RIGHT;

	//player mini
	sprites[SPRITE_INFO_PLAYER_MINI]->InitFromFile("assets/sprites/player-mini");
	sprites[SPRITE_INFO_PLAYER_MINI]->image->direction = TEXTURE_DIRECTION_RIGHT;

}
SpriteManager::~SpriteManager()
{
}
