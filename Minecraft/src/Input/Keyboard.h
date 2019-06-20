#pragma once

#include <map>

class Keyboard
{
public:
	static void updateKey(int key, int state);

	static bool isReleased(int key);
	static bool isPressed(int key);
	static bool isRepeated(int key);

private:
	static std::map<int, int> mKeys;
};