#include "World.h"
#include"Camera.h"
#include"Player.h"
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

using namespace std;

#include"Collision.h"
#include "AriseBase.h"

void World::Init(const char* tilesheetPath,
	const char* matrixPath,
	const char* objectsPath,
	const char* collisionTypeCollidePath,
	const char* spacePath,
	const char* quadTreePath)
{


	/* khởi tạo vị trí player */


	Player::getPlayerMini()->set(52, 350, 16, 18);
	Player::getPlayerMain()->set(52, 350, 16, 18);
	Player::changeToPlayerMain();

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
		case SPRITE_INFO_GATE:
			obj = new Gate();
			((Gate*)obj)->world = this;
			break;

		case SPRITE_INFO_WORM:
			obj = new Worm();
			break;
		case SPRITE_INFO_DOMES:
			obj = new Domes();
			break;
		case SPRITE_INFO_FLOATER:
			obj = new Floater();
			break;
		case SPRITE_INFO_GUNNER:
			obj = new Gunner();
			break;
		case SPRITE_INFO_INSECT:
			obj = new Insect();
			break;
		case SPRITE_INFO_ORBS:
			obj = new Orbs();
			break;
		case SPRITE_INFO_SKULLS:
			obj = new Skulls();
			break;
		case SPRITE_INFO_SNAILS:
			obj = new Snails();
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

		for (int i = 0; i < customPropertyCount; i = i+1)
		{
			string key, value;
			fs >> key;
			fs >> value;
			obj->customProperties.insert(std::pair<string,string>(key, value));
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
	setCurrentSpace(6);
	resetLocationInSpace();
	changeSpace = CHANGE_SPACE_UPDATE;
}

void World::Init(const char* folderPath)
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

Tilemap* World::getTileMap()
{
	return &tilemap;
}

void World::update(float dt)
{
	Camera* camera = Camera::getInstance();
	auto player = Player::getInstance();
	switch (changeSpace)
	{
	case CHANGE_SPACE_START:
		changeSpace = CHANGE_SPACE_MOVING;
		player->setRenderActive(false);
		if (changeSpaceCameraX > camera->getX())
		{
			cameraMoveDx = 2;
		}
		else
		{
			cameraMoveDx = -2;
		}
		if (changeSpaceCameraY > camera->getY())
		{
			cameraMoveDy = 2;
		}
		else
		{
			cameraMoveDy = -2;
		}
		break;
	case CHANGE_SPACE_MOVING:
	{
		if (cameraMoveDx > 0 && changeSpaceCameraX > camera->getX() || cameraMoveDx < 0 && changeSpaceCameraX < camera->getX())
		{
			camera->setDx(cameraMoveDx);
		}
		else
		{
			camera->setDx(0);
			cameraMoveDx = 0;
		}

		if (cameraMoveDy > 0 && changeSpaceCameraY > camera->getY() || cameraMoveDy < 0 && changeSpaceCameraY < camera->getY())
		{
			camera->setDy(cameraMoveDy);
		}
		else
		{
			camera->setDy(0);
			cameraMoveDy = 0;
		}
		if (cameraMoveDx == 0 && cameraMoveDy == 0)
		{
			changeSpace = CHANGE_SPACE_MOVING_END;
		}

		auto preventCameras = objectCategories.at(COLLISION_TYPE_PREVENT_CAMERA);
		for (int i = 0; i < preventCameras->Count; i++)
		{
			auto obj = preventCameras->at(i);
			Collision::CheckCollision(camera, obj);
		}
		camera->goX();
		camera->goY();
		break;
	}
	case CHANGE_SPACE_MOVING_END:
		player->setX(changeSpacePlayerX);
		player->setY(changeSpacePlayerY);
		changeSpace = CHANGE_SPACE_UPDATE;
		player->setRenderActive(true);
		break;
	case CHANGE_SPACE_UPDATE:
	{
		quadTree.fillObjectsToCamera();
		KEY* key = KEY::getInstance();
		/* cập nhật key */
		key->update();

		/* chuyển space khi nhấn phím */
		if (key->isSpace0Down)
		{
			setCurrentSpace(0);
			resetLocationInSpace();
		}
		if (key->isSpace1Down)
		{
			setCurrentSpace(1);
			resetLocationInSpace();
		}
		if (key->isSpace2Down)
		{
			setCurrentSpace(2);
			resetLocationInSpace();
		}
		if (key->isSpace3Down)
		{
			setCurrentSpace(3);
			resetLocationInSpace();
		}
		if (key->isSpace4Down)
		{
			setCurrentSpace(4);
			resetLocationInSpace();
		}
		if (key->isSpace5Down)
		{
			setCurrentSpace(5);
			resetLocationInSpace();
		}
		if (key->isSpace6Down)
		{
			setCurrentSpace(6);
			resetLocationInSpace();
		}
		if (key->isSpace7Down)
		{
			setCurrentSpace(7);
			resetLocationInSpace();
		}
		if (key->isSpace8Down)
		{
			setCurrentSpace(8);
			resetLocationInSpace();
		}
		if (key->isSpace10Down)
		{
			setCurrentSpace(10);
			resetLocationInSpace();
		}
		if (key->isSpace11Down)
		{
			setCurrentSpace(11);
			resetLocationInSpace();
		}
		if (key->isSpace12Down)
		{
			setCurrentSpace(12);
			resetLocationInSpace();
		}
		if (key->isSpace13Down)
		{
			setCurrentSpace(13);
			resetLocationInSpace();
		}
		if (key->isSpace14Down)
		{
			setCurrentSpace(14);
			resetLocationInSpace();
		}
		if (key->isSpaceBossDown)
		{
			setCurrentSpace(9);
			resetLocationInSpace();
		}

		auto ariseObjects = AriseBase::getAriseObjects();

		/* cập nhật đối tượng */
		for (size_t i = 0; i < camera->allObjects->Count; i++)
		{
			auto obj = camera->allObjects->at(i);
			obj->update(dt);
			Collision::CheckCollision(Player::getPlayerMain(), obj);
			Collision::CheckCollision(Player::getPlayerMini(), obj);
			Collision::CheckCollision(Player::getPlayerMini(), obj);

			for (size_t i2 = 0; i2 < ariseObjects->size(); i2++)
			{
				/* cho xét va chạm của đối tượng dựa vào 1 cặp collisionType trong CollisionTypeCollide */
				Collision::CheckCollision(ariseObjects->at(i2), obj);
			}
		}

		for (size_t i2 = 0; i2 < ariseObjects->size(); i2++)
		{
			/* cho xét va chạm của đối tượng dựa vào 1 cặp collisionType trong CollisionTypeCollide */
			Collision::CheckCollision(Player::getPlayerMain(), ariseObjects->at(i2));
			Collision::CheckCollision(Player::getPlayerMini(), ariseObjects->at(i2));
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

		Player::updatePlayer(dt);
		Camera::getInstance()->update();
		break;
	}
	default:
		break;
	}
}

void World::setCurrentSpace(int spaceIndex)
{
	this->currentSpace = spaces.at(spaceIndex);
	Camera::getInstance()->setSpace(this->currentSpace);
}

Space* World::getCurrentSpace()
{
	return currentSpace;
}

void World::resetLocationInSpace()
{
	Camera* camera = Camera::getInstance();

	camera->setLocation(getCurrentSpace()->CameraX, getCurrentSpace()->CameraY);
	Player::getPlayerMain()->setLocation(getCurrentSpace()->PlayerX, getCurrentSpace()->PlayerY);
	Player::getPlayerMini()->setLocation(getCurrentSpace()->PlayerX, getCurrentSpace()->PlayerY);
}

void World::render()
{
	Camera* camera = Camera::getInstance();
	tilemap.render(camera);
	for (size_t i = 0; i < camera->allObjects->Count; i++)
	{
		/* vẽ đối tượng */
		camera->allObjects->at(i)->render();
	}
	AriseBase::renderAriseObjects();
	Player::renderPlayer();
}

World::World()
{
}
World::~World()
{
}
