#pragma once
#include<Windows.h>
class KEY
{
public:
	bool
		isLeftDown,
		isRightDown,
		isUpDown,
		isDownDown,
		/* sẽ bằng true nếu bạn giữ key jump */
		isJumpDown,
		isPreviousJumpDown,
		/* sẽ bằng true nếu bạn chỉ nhấn key jump lần đầu. nếu lần sau vẫn giữ key jump thì nó sẽ là false */
		isJumpPress,
		isAttackDown,

		isSpace0Down,
		isSpace1Down,
		isSpace2Down,
		isSpace3Down,
		isSpace4Down,
		isSpace5Down,
		isSpace6Down,
		isSpace7Down,
		isSpace8Down,
		isSpace14Down,
		isSpace10Down,
		isSpace11Down,
		isSpace12Down,
		isSpace13Down,
		isSpaceBossDown,

		isEnterDown,
		changePlayerDown,
		previousChangePlayerDown,
		isSubWeaponDown,
		changePlayer;
		

	static KEY* instance;
	static KEY* getInstance();

	void update();
	
	KEY();
	~KEY();
};

