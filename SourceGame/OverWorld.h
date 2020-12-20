#pragma once
#include"Tilemap.h"
#include"SpriteManager.h"
#include"BaseObject.h"
#include"CollisionTypeCollide.h"
#include"Space.h"



class OverWorld
{
	/* dùng tilemap để vẽ map */
	Tilemap tilemap;

	/* tất cả object có trong world */
	List<BaseObject*> allObjects;

	/* danh sách collisionTypeCollide */
	List<CollisionTypeCollide*> collisionTypeCollides;
	/* danh sách object được phân loại theo collision_type */
	List<List<BaseObject*>*> objectCategories;

	/* danh sách space trong world */
	List<Space*> spaces;

	/* space hiện tại */
	Space* currentSpace;

public:

	void Init(const char* tilesheetPath,
		const char* matrixPath, 
		const char* objectsPath,
		const char* collisionTypeCollidePath,
		const char* spacePath);
	void Init(const char* folderPath);

	Tilemap* getTileMap();
	
	/* cập nhật các đối tượng trong game */
	void update(float dt);

	/* setCurrentSpace */
	void setCurrentSpace(int spaceIndex);

	Space* getCurrentSpace();

	/* reset camera va player dua vao currentSpace */
	void resetLocationInSpace();

	/* vẽ các đối tượng trong game */
	void render();
	OverWorld();
	~OverWorld();
};

