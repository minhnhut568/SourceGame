#pragma once

/* sử dụng list */
#include"List.h"
#include"Sprite.h"

/* khai báo 1 define viết tắt cho chữ SpriteManager::getSprite */
#define SPR SpriteManager::getSprite

/* ta tạo 1 sprite info để lưu thông tin của các sprite */
enum SPRITE_INFO
{
	SPRIET_INFO_GATE = -2,

	/* đối tượng không có hình ảnh ta sẽ đặt số âm */
	SPRITE_INFO_GROUND = -1,

	/* đối tượng có hình ảnh ta sẽ đặt số dương */
	SPRITE_INFO_PLAYER = 0,

	SPRITE_INFO_BULLET = 2, /* 1.png sẽ tương ứng với sprite này */

	SPRITE_INFO_WORM = 3,

	SPRITE_INFO_PLAYER_MINI = 4,

	SPRITE_INFO_PLAYER_MINI_BULLET = 5,

	// thêm các sprite_info khác ở đây

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

