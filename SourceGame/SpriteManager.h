#pragma once

/* sử dụng list */
#include"List.h"
#include"Sprite.h"

/* khai báo 1 define viết tắt cho chữ SpriteManager::getSprite */
#define SPR SpriteManager::getSprite

/* ta tạo 1 sprite info để lưu thông tin của các sprite */
enum SPRITE_INFO
{
	SPRITE_INFO_GATE = -2,

	/* đối tượng không có hình ảnh ta sẽ đặt số âm */
	SPRITE_INFO_GROUND = -1,

	/* đối tượng có hình ảnh ta sẽ đặt số dương */
	SPRITE_INFO_PLAYER = 0,

	SPRITE_INFO_BULLET = 2, /* 1.png sẽ tương ứng với sprite này */

	SPRITE_INFO_WORM = 3,

	SPRITE_INFO_PLAYER_MINI = 4,

	SPRITE_INFO_PLAYER_MINI_BULLET = 5,

	SPRITE_INFO_DOMES = 6,

	SPRITE_INFO_FLOATER = 7,

	SPRITE_INFO_FLOATER_BULLET = 8,

	SPRITE_INFO_GUNNER = 9,

	SPRITE_INFO_INSECT = 10,

	SPRITE_INFO_ORBS = 11,

	SPRITE_INFO_SKULLS = 12,

	SPRITE_INFO_SKULLS_BULLET = 13,

	SPRITE_INFO_BOOM = 14,

	SPRITE_INFO_SNAILS = 15,

	SPRITE_INFO_PLAYER_ONE_WORLD = 16,

	SPRITE_INFO_PLAYER_OVER_WORLD_BULLET = 17,

	SPRITE_INFO_CANNONS = 18,

	SPRITE_INFO_BOSS = 20,

	SPRITE_INFO_BOSS_BODY = 21,

	SPRITE_INFO_ITEM_P = 22,

	SPRITE_INFO_INTRO = 23,

	SPRITE_INFO_OVERWORLD_BULLET = 24,

	SPRITE_INFO_TELEPORTER = 25,

	SPRITE_INFO_INTRO_STORY = 26,

	SPRITE_INFO_INTRO_TITLE = 27,

	SPRITE_INFO_INTRO_CAR = 28,

	SPRITE_INFO_ENDGAME_HEAD = 29,

	SPRITE_INFO_STONE = 30,

	SPRITE_INFO_STONE2 = 31,

	SPRITE_INFO_STONE3 = 32,

	SPRITE_INFO_ROCK = 33,

	SPRITE_INFO_BOSS_BULLET = 34,

	SPRITE_INFO_EYEBALLS = 40,

	SPRITE_COUNT
};

class SpriteManager
{
	/* ta lưu tất cả sprite ở đây */
	List<Sprite*> sprites;

	/* singleton pattern */
	static SpriteManager* instance;
public:
	static SpriteManager* getInstance();

	/* dùng để lấy sprite từ spriteManager */
	static Sprite* getSprite(int spriteInfo);

	SpriteManager();
	~SpriteManager();
};

