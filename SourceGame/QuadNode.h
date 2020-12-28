#pragma once
#include "BaseObject.h"
#include"List.h"
#include"Camera.h"

class QuadNode 
	: public Rect
{
public:
	QuadNode();
	int nodeId;
	int nodeCount;
	List<BaseObject*> objects;
	QuadNode* LeftTop;
	QuadNode* RightTop;
	QuadNode* LeftBottom;
	QuadNode* RightBottom;

	void fillObjectsToCamera();

};

