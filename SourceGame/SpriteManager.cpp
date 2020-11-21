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

	/* thêm sprite ở đây */

	/* đăng ký sprite cho simon */
	sprites[SPRITE_INFO_PLAYER]->InitFromFile("assets/sprites/player");
	sprites[SPRITE_INFO_PLAYER]->image->direction = TEXTURE_DIRECTION_RIGHT;

	// bullet
	sprites[SPRITE_INFO_BULLET]->InitFromImage("assets/sprites/bullet/image.png");
	sprites[SPRITE_INFO_BULLET]->image->direction = TEXTURE_DIRECTION_LEFT;

}
SpriteManager::~SpriteManager()
{
}
