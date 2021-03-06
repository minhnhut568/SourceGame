#pragma once
enum COLLISION_TYPE
{
	COLLISION_TYPE_GROUND,

	COLLISION_TYPE_ENEMY,

	COLLISION_TYPE_ITEM,

	COLLISION_TYPE_PLAYER,
	
	COLLISION_TYPE_GATE,

	COLLISION_TYPE_LADDER,

	COLLISION_TYPE_GATE_OVER_WORLD_SPACE0,

	COLLISION_TYPE_GATE_OVER_WORLD_SPACE1,

	COLLISION_TYPE_GATE_OVER_WORLD_SPACE2,

	COLLISION_TYPE_PREVENT_CAMERA,

	COLLISION_TYPE_GATE_OVER_WORLD_SPACE4,

	COLLISION_TYPE_COUNT
};

enum COLLISION_TYPE_OVER_WORLD
{
	COLLISION_TYPE_OVER_WORLD_GROUND,

	COLLISION_TYPE_OVER_WORLD_ENEMY,

	COLLISION_TYPE_GATE_TO_WORLD_SPACE6,

	COLLISION_TYPE_GATE_TO_WORLD_SPACE4,

	COLLISION_TYPE_GATE_TO_WORLD_SPACE5,

	COLLISION_TYPE_GATE_TO_WORLD_SPACE9,
};