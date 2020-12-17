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
	/* nếu lần trước chưa nhấn key jump mà lần này nhấn key jump thì isJumpPress sẽ là true */
	isJumpPress = (isPreviousJumpDown==false && isJumpDown==true);

	/* chuyển space */
	isSpace1Down = GetAsyncKeyState(getKeyChar('q'));
	isSpace2Down = GetAsyncKeyState(getKeyChar('w'));
	isSpace3Down = GetAsyncKeyState(getKeyChar('e'));
	isSpace4Down = GetAsyncKeyState(getKeyChar('r'));
	isSpace5Down = GetAsyncKeyState(getKeyChar('t'));
	isSpaceTestDown = GetAsyncKeyState(getKeyChar('p'));
	changePlayer = (previousChangePlayerDown == false && changePlayerDown == true);
}

KEY::KEY()
{
}


KEY::~KEY()
{
}
