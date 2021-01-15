#include "KEY.h"

DWORD getKeyChar(char keyChar)
{
	return ((int)keyChar - 'a') + 0x41;
}

KEY * KEY::instance = 0;
KEY * KEY::getInstance()
{
	if (instance == 0)
		instance = new KEY();
	return instance;
}

void KEY::update()
{
	isUpDown = GetAsyncKeyState(VK_UP);
	isDownDown = GetAsyncKeyState(VK_DOWN);
	isLeftDown = GetAsyncKeyState(VK_LEFT);
	isRightDown = GetAsyncKeyState(VK_RIGHT); 

	isEnterDown = GetAsyncKeyState(VK_RETURN);

	/* lần trước đó có phải là nhấn key jump hay không */
	isPreviousJumpDown = isJumpDown;
	/* giả sử nhấn key x là player sẽ nhảy */
	isJumpDown = GetAsyncKeyState(getKeyChar('x'));
	isAttackDown = GetAsyncKeyState(getKeyChar('z'));

	previousChangePlayerDown = changePlayerDown;
	changePlayerDown = GetAsyncKeyState(VK_RSHIFT);
	isSubWeaponDown = GetAsyncKeyState(getKeyChar('x'));
	/* nếu lần trước chưa nhấn key jump mà lần này nhấn key jump thì isJumpPress sẽ là true */
	isJumpPress = (isPreviousJumpDown==false && isJumpDown==true);

	/* chuyển space */
	isSpace0Down = GetAsyncKeyState(getKeyChar('q'));
	isSpace1Down = GetAsyncKeyState(getKeyChar('w'));
	isSpace2Down = GetAsyncKeyState(getKeyChar('e'));
	isSpace3Down = GetAsyncKeyState(getKeyChar('r'));
	isSpace4Down = GetAsyncKeyState(getKeyChar('t'));
	isSpace5Down = GetAsyncKeyState(getKeyChar('y'));
	isSpace6Down = GetAsyncKeyState(getKeyChar('u'));
	isSpace7Down = GetAsyncKeyState(getKeyChar('i'));
	isSpace8Down = GetAsyncKeyState(getKeyChar('o'));
	isSpace10Down = GetAsyncKeyState(getKeyChar('p'));
	isSpace11Down = GetAsyncKeyState(getKeyChar('l'));
	isSpace12Down = GetAsyncKeyState(getKeyChar('k'));
	isSpace13Down = GetAsyncKeyState(getKeyChar('j'));
	isSpace14Down = GetAsyncKeyState(getKeyChar('h'));

	isSpaceBossDown = GetAsyncKeyState(getKeyChar('b'));
	changePlayer = (previousChangePlayerDown == false && changePlayerDown == true);
}

KEY::KEY()
{
}


KEY::~KEY()
{
}
