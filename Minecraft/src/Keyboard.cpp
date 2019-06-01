#include <iostream>
#include <GLFW/glfw3.h>
#include "Keyboard.h"

std::map<int, int> Keyboard::m_keys;

void Keyboard::UpdateKey(int key, int state)
{
	m_keys[key] = state;

	std::cout << "[INFO/Keyboard] Updated key " << key << " to state " << state << std::endl;
}

bool Keyboard::IsPressed(int key)
{
	return m_keys[key] == GLFW_PRESS || m_keys[key] == GLFW_REPEAT;
}

bool Keyboard::IsRepeated(int key)
{
	return m_keys[key] == GLFW_REPEAT;
}

bool Keyboard::IsReleased(int key)
{
	return m_keys[key] == GLFW_RELEASE;
}
