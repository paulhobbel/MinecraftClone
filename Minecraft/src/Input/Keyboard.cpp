#include <GLFW/glfw3.h>
#include "Keyboard.h"

std::map<int, int> Keyboard::mKeys;

void Keyboard::updateKey(int key, int state)
{
	mKeys[key] = state;
}

bool Keyboard::isPressed(int key)
{
	return mKeys[key] == GLFW_PRESS || mKeys[key] == GLFW_REPEAT;
}

bool Keyboard::isRepeated(int key)
{
	return mKeys[key] == GLFW_REPEAT;
}

bool Keyboard::isReleased(int key)
{
	return mKeys[key] == GLFW_RELEASE;
}
