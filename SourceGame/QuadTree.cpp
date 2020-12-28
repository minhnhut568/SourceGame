#include "QuadTree.h"
#include<fstream>
#include<map>
#include"Collision.h"
using namespace std;

extern int readLineCount(const char* filename);

void QuadTree::init(const char* quadTreePath, List<BaseObject*>* allObjects, int mapHeight)
{
	int lineCount = readLineCount(quadTreePath);
	
	ifstream fs(quadTreePath);

	int nodeCount = lineCount - 1;

	int nodeId, x, y, w, h, nodeChildsCount, objectsCount;

	map<int, QuadNode*> quadNodeMap;

	for (size_t i = 0; i < nodeCount; i++)
	{
		QuadNode* node = new QuadNode();
		fs >> nodeId >> x >> y >> w >> h >> nodeChildsCount >> objectsCount;
		node->nodeId = nodeId;
		node->set(x, mapHeight - y, w, h);
		node->nodeCount = nodeChildsCount;
		for (size_t j = 0; j < objectsCount; j++)
		{
			int objectIndex;
			fs >> objectIndex;

			BaseObject* obj = allObjects->at(objectIndex);
			node->objects._Add(obj);
		}

		quadNodeMap.insert(pair<int, QuadNode*>(nodeId, node));

		if (i > 0)
		{
			int parentId = nodeId / 10;
			int nodeType = nodeId % 10;

			QuadNode* parent = quadNodeMap.at(parentId);
			switch (nodeType)
			{
			case 1:
				parent->LeftTop = node;
				break;
			case 2:
				parent->RightTop = node;
				break;
			case 3:
				parent->LeftBottom = node;
				break;
			case 4:
				parent->RightBottom = node;
				break;
			default:
				break;
			}
		}
		else
		{
			rootNode = node;
		}
	}
}

void QuadTree::fillObjectsToCamera()
{
	Camera* camera = Camera::getInstance();
	for (size_t i = 0; i < camera->allObjects->Count; i++)
	{
		auto obj = camera->allObjects->at(i);
		if (!Collision::AABBCheck(camera, obj) && !Collision::AABBCheck(camera, &obj->initBox))
		{
			obj->onInitLocation();
			Camera::getInstance()->removeObject(obj);
		}
	}
	rootNode->fillObjectsToCamera();
}
