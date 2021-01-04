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

	//domes
	sprites[SPRITE_INFO_DOMES]->InitFromFile("assets/sprites/domes");
	sprites[SPRITE_INFO_DOMES]->image->direction = TEXTURE_DIRECTION_LEFT;

	//floater
	sprites[SPRITE_INFO_FLOATER]->InitFromFile("assets/sprites/floater");
	sprites[SPRITE_INFO_FLOATER]->image->direction = TEXTURE_DIRECTION_LEFT;

	//player mini
	sprites[SPRITE_INFO_PLAYER_MINI]->InitFromFile("assets/sprites/player-mini");
	sprites[SPRITE_INFO_PLAYER_MINI]->image->direction = TEXTURE_DIRECTION_RIGHT;

	//player mini
	sprites[SPRITE_INFO_PLAYER_MINI_BULLET]->InitFromFile("assets/sprites/player-mini-bullet");
	sprites[SPRITE_INFO_PLAYER_MINI_BULLET]->image->direction = TEXTURE_DIRECTION_RIGHT;

	//player mini
	sprites[SPRITE_INFO_FLOATER_BULLET]->InitFromFile("assets/sprites/floater-bullet");
	sprites[SPRITE_INFO_FLOATER_BULLET]->image->direction = TEXTURE_DIRECTION_RIGHT;

	//gunner
	sprites[SPRITE_INFO_GUNNER]->InitFromFile("assets/sprites/gunner");
	sprites[SPRITE_INFO_GUNNER]->image->direction = TEXTURE_DIRECTION_RIGHT;

	//insect
	sprites[SPRITE_INFO_INSECT]->InitFromFile("assets/sprites/insect");
	sprites[SPRITE_INFO_INSECT]->image->direction = TEXTURE_DIRECTION_RIGHT;

	//orbs
	sprites[SPRITE_INFO_ORBS]->InitFromFile("assets/sprites/orbs");
	sprites[SPRITE_INFO_ORBS]->image->direction = TEXTURE_DIRECTION_RIGHT;
	
	//skulls
	sprites[SPRITE_INFO_SKULLS]->InitFromFile("assets/sprites/skulls");
	sprites[SPRITE_INFO_SKULLS]->image->direction = TEXTURE_DIRECTION_RIGHT;

	//skulls bullet
	sprites[SPRITE_INFO_SKULLS_BULLET]->InitFromFile("assets/sprites/skulls-bullet");
	sprites[SPRITE_INFO_SKULLS_BULLET]->image->direction = TEXTURE_DIRECTION_RIGHT;
	
	//boom
	sprites[SPRITE_INFO_BOOM]->InitFromFile("assets/sprites/boom");
	sprites[SPRITE_INFO_BOOM]->image->direction = TEXTURE_DIRECTION_RIGHT;
	
	//snails
	sprites[SPRITE_INFO_SNAILS]->InitFromFile("assets/sprites/snails");
	sprites[SPRITE_INFO_SNAILS]->image->direction = TEXTURE_DIRECTION_RIGHT;
	
	//SPRITE_INFO_PLAYER_OVER_WORLD
	sprites[SPRITE_INFO_PLAYER_ONE_WORLD]->InitFromFile("assets/sprites/player-oneworld");
	sprites[SPRITE_INFO_PLAYER_ONE_WORLD]->image->direction = TEXTURE_DIRECTION_LEFT;

	//SPRITE_INFO_PLAYER_OVER_WORLD_BULLET
	sprites[SPRITE_INFO_PLAYER_OVER_WORLD_BULLET]->InitFromFile("assets/sprites/player-mini-overworld-bullet");
	sprites[SPRITE_INFO_PLAYER_OVER_WORLD_BULLET]->image->direction = TEXTURE_DIRECTION_LEFT;

	//SPRITE_INFO_CANNONS
	sprites[SPRITE_INFO_CANNONS]->InitFromFile("assets/sprites/cannons");
	sprites[SPRITE_INFO_CANNONS]->image->direction = TEXTURE_DIRECTION_LEFT;

	//SPRITE_INFO_BOSS
	sprites[SPRITE_INFO_BOSS]->InitFromFile("assets/sprites/boss");
	sprites[SPRITE_INFO_BOSS]->image->direction = TEXTURE_DIRECTION_LEFT;

	//SPRITE_INFO_BOSS_BODY
	sprites[SPRITE_INFO_BOSS_BODY]->InitFromFile("assets/sprites/boss-body");
	sprites[SPRITE_INFO_BOSS_BODY]->image->direction = TEXTURE_DIRECTION_LEFT;

	//SPRITE_INFO_ITEM_P
	sprites[SPRITE_INFO_ITEM_P]->InitFromImage("assets/sprites/item_p/item_p.png");
	sprites[SPRITE_INFO_ITEM_P]->image->direction = TEXTURE_DIRECTION_LEFT;

}
SpriteManager::~SpriteManager()
{
}
