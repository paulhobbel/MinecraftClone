#include "Mouse.h"
#include "../GameWindow.h"

glm::dvec2 Mouse::getPosition()
{
	return glm::dvec2();
}

glm::dvec2 Mouse::getPosition(GameWindow* window)
{
	glm::dvec2 position;
	glfwGetCursorPos(window->getHandle(), &position.x, &position.y);
	return position;
}

void Mouse::setPosition(glm::dvec2 position, GameWindow* window)
{
	glfwSetCursorPos(window->getHandle(), position.x, position.y);
}
