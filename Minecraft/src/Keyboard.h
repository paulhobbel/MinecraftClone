#pragma once

#include <map>

class Keyboard
{
public:
	static void updateKey(int key, int state);

	static bool IsReleased(int key);
	static bool IsPressed(int key);
	static bool IsRepeated(int key);

private:
	static std::map<int, int> m_keys;
};