#pragma once
#include"Tilemap.h"
#include"SpriteManager.h"
#include"BaseObject.h"
#include"CollisionTypeCollide.h"
#include"Space.h"
#include "QuadTree.h"
#include "Sound.h"

enum CHANGE_SPACE
{
	CHANGE_SPACE_START,
	CHANGE_SPACE_MOVING,
	CHANGE_SPACE_MOVING_END,
	CHANGE_SPACE_UPDATE
};

class World
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

	QuadTree quadTree;

public:
	CHANGE_SPACE changeSpace;

	int changeSpaceCameraX;
	int changeSpaceCameraY;
	int changeSpacePlayerX;
	int changeSpacePlayerY;
	int cameraMoveDx;
	int cameraMoveDy;

	void Init(const char* tilesheetPath,
		const char* matrixPath, 
		const char* objectsPath,
		const char* collisionTypeCollidePath,
		const char* spacePath,
		const char* quadTreePath);
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
	World();
	~World();
};

