#include "OverWorld.h"
#include"Camera.h"
#include"PlayerOverWorld.h"
#include"KEY.h"
#include <string>
#include "Gate.h"
#include "Worm.h"
#include "Domes.h"
#include "Floater.h"
#include "FloaterBullet.h"
#include "Gunner.h"
#include "Insect.h"
#include "Orbs.h"
#include "Skulls.h"
#include "Snails.h"
#include "Player.h"
#include "PlayerOverWorld.h"
#include "Cannons.h"
#include "Boss.h"
#include "Teleporter.h"

using namespace std;

#include"Collision.h"
#include "AriseBase.h"

void OverWorld::Init(const char* tilesheetPath,
	const char* matrixPath,
	const char* objectsPath,
	const char* collisionTypeCollidePath,
	const char* spacePath,
	const char* quadTreePath)
{
	/* khởi tạo tilemap */
	tilemap.Init(tilesheetPath, matrixPath);

	int worldHeight = tilemap.getWorldHeight();

	/* khởi tạo phân loại đối tượng */
	for (size_t i = 0; i < COLLISION_TYPE_COUNT; i++)
	{
		objectCategories._Add(new List<BaseObject*>());
	}

	/* khởi tạo đối tượng */
	int objectCount;
	ifstream fs(objectsPath);
	fs >> objectCount;
	for (size_t i = 0; i < objectCount; i++)
	{
		BaseObject* obj;
		int id;
		/* đọc id đối tượng */
		fs >> id;
		switch (id)
		{
		case SPRITE_INFO_CANNONS:
			obj = new Cannons();
			break;
		case SPRITE_INFO_BOSS:
			obj = new Boss();
			break;
		case SPRITE_INFO_TELEPORTER:
			obj = new Teleporter();
			break;
		default:
			obj = new BaseObject();
			break;
		}
		/* đọc thông số của đối tượng */
		obj->onInitFromFile(fs, worldHeight);
		if (id >= 0)
		{
			/* nếu id đối tượng không âm tức đối tượng có sprite ta gán sprite cho nó */
			obj->setSprite(SPR(id));
		}

		int customPropertyCount = 0;
		fs >> customPropertyCount;

		for (int i = 0; i < customPropertyCount; i = i + 1)
		{
			string key, value;
			fs >> key;
			fs >> value;
			obj->customProperties.insert(std::pair<string, string>(key, value));
		}

		/* thêm đối tượng vào danh sách */
		allObjects._Add(obj);

		/* thêm object vào từng loại đối tượng */
		objectCategories.at(obj->getCollisionType())->_Add(obj);

	}

	quadTree.init(quadTreePath, &allObjects, tilemap.getWorldHeight());

	/* đọc collisiontype collide */
	int numberOfCollisionTypeCollides = 0;
	ifstream fsColli(collisionTypeCollidePath);
	fsColli >> numberOfCollisionTypeCollides;
	for (size_t i = 0; i < numberOfCollisionTypeCollides; i++)
	{

		int collisionType1, collisionType2;
		fsColli >> collisionType1 >> collisionType2;
		CollisionTypeCollide* collisionTypeCollide = new CollisionTypeCollide();
		collisionTypeCollide->COLLISION_TYPE_1 = (COLLISION_TYPE)collisionType1;
		collisionTypeCollide->COLLISION_TYPE_2 = (COLLISION_TYPE)collisionType2;
		collisionTypeCollides._Add(collisionTypeCollide);
	}

	/* đọc space */
	int numberOfSpaces = 0;
	ifstream fsSpace(spacePath);

	/* enter 1 dòng */
	ignoreLineIfstream(fsSpace, 1);
	fsSpace >> numberOfSpaces;
	for (size_t i = 0; i < numberOfSpaces; i++)
	{
		/* enter 4 dòng */
		ignoreLineIfstream(fsSpace, 4);
		Space* space = new Space();
		fsSpace >> space->X >> space->Y >> space->Width >> space->Height;

		/* enter 2 dòng */
		ignoreLineIfstream(fsSpace, 2);
		fsSpace >> space->CameraX >> space->CameraY;

		/* enter 2 dòng */
		ignoreLineIfstream(fsSpace, 2);
		fsSpace >> space->PlayerX >> space->PlayerY;

		/* do chiều y của trong file định nghĩa ngược với chiều logic nên cần đổi lại */
		space->CameraY = worldHeight - space->CameraY;
		space->PlayerY = worldHeight - space->PlayerY;
		space->Y = worldHeight - space->Y;

		/* thêm vào space */
		spaces._Add(space);
	}

	/* bắt đầu từ space 0 */
	setCurrentSpace(0);
	resetLocationInSpace();
}

void OverWorld::Init(const char* folderPath)
{
	/* tìm đường dẫn tilesheet và matrix object */
	string folderPathString = (string)folderPath;

	string tilesheetString = folderPathString;
	tilesheetString.append("/tilesheet.png");

	string matrixPathString = folderPathString;
	matrixPathString.append("/matrix.dat");

	string objectPathString = folderPathString;
	objectPathString.append("/objects.dat");

	string collisionTypeCollidePath = folderPathString;
	collisionTypeCollidePath.append("/collision_type_collides.dat");

	string spacePath = folderPathString;
	spacePath.append("/spaces.dat");

	string quadTreePath = folderPathString;
	quadTreePath.append("/quadtree.dat");

	Init(tilesheetString.c_str(),
		matrixPathString.c_str(),
		objectPathString.c_str(),
		collisionTypeCollidePath.c_str(),
		spacePath.c_str(),
		quadTreePath.c_str());
}

Tilemap* OverWorld::getTileMap()
{
	return &tilemap;
}

void OverWorld::update(float dt)
{
	Camera* camera = Camera::getInstance();
	auto player = PlayerOverWorld::getInstance();
	quadTree.fillObjectsToCamera();

	KEY* key = KEY::getInstance();
	/* cập nhật key */
	key->update();


	auto ariseObjects = AriseBase::getAriseObjects();

	/* cập nhật đối tượng */
	for (size_t i = 0; i < camera->allObjects->Count; i++)
	{
		auto obj = camera->allObjects->at(i);
		obj->update(dt);
		Collision::CheckCollision(PlayerOverWorld::getInstance(), obj);

		for (size_t i2 = 0; i2 < ariseObjects->size(); i2++)
		{
			/* cho xét va chạm của đối tượng dựa vào 1 cặp collisionType trong CollisionTypeCollide */
			Collision::CheckCollision(ariseObjects->at(i2), obj);
		}
	}

	for (size_t i2 = 0; i2 < ariseObjects->size(); i2++)
	{
		/* cho xét va chạm của đối tượng dựa vào 1 cặp collisionType trong CollisionTypeCollide */
		Collision::CheckCollision(PlayerOverWorld::getInstance(), ariseObjects->at(i2));
	}

	/* xét va chạm cho các loại đối tượng với nhau */
	for (size_t i = 0; i < collisionTypeCollides.size(); i++)
	{
		COLLISION_TYPE col1 = collisionTypeCollides.at(i)->COLLISION_TYPE_1;
		COLLISION_TYPE col2 = collisionTypeCollides.at(i)->COLLISION_TYPE_2;

		/* danh sách đối tượng thuộc collision type 1 */
		List<BaseObject*>* collection1 = camera->objectCategories.at(col1);
		/* danh sách đối tượng thuộc collision type 2 */
		List<BaseObject*>* collection2 = camera->objectCategories.at(col2);

		for (size_t i1 = 0; i1 < collection1->size(); i1++)
		{
			for (size_t i2 = 0; i2 < collection2->size(); i2++)
			{
				/* cho xét va chạm của đối tượng dựa vào 1 cặp collisionType trong CollisionTypeCollide */
				Collision::CheckCollision(collection1->at(i1), collection2->at(i2));
			}
		}
	}

	PlayerOverWorld::getInstance()->update(dt);
	Player::updatePlayer(dt);
	Camera::getInstance()->update();
}

void OverWorld::setCurrentSpace(int spaceIndex)
{
	this->currentSpace = spaces.at(spaceIndex);
	Camera::getInstance()->setSpace(this->currentSpace);
}

Space* OverWorld::getCurrentSpace()
{
	return currentSpace;
}

void OverWorld::resetLocationInSpace()
{
	Camera* camera = Camera::getInstance();
	camera->setLocation(getCurrentSpace()->CameraX, getCurrentSpace()->CameraY);
	PlayerOverWorld::getInstance()->setLocation(getCurrentSpace()->PlayerX, getCurrentSpace()->PlayerY);
}

void OverWorld::render()
{
	Camera* camera = Camera::getInstance();
	tilemap.render(Camera::getInstance());
	for (size_t i = 0; i < camera->allObjects->Count; i++)
	{
		/* vẽ đối tượng */
		camera->allObjects->at(i)->render();
	}
	AriseBase::renderAriseObjects();
	PlayerOverWorld::getInstance()->render();

	for (size_t i = 0; i < camera->objectCategories[5]->Count; i++)
	{
		/* vẽ đối tượng */
		camera->objectCategories[5]->at(i)->render();
	}
}

OverWorld::OverWorld()
{
}
OverWorld::~OverWorld()
{
}
