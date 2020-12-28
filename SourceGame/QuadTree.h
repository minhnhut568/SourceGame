#pragma once
#include"QuadNode.h"
class QuadTree
{
public:
	QuadNode* rootNode;

	void init(const char* quadTreePath, List<BaseObject*>* allObjects, int mapHeight);

	void fillObjectsToCamera();
};

