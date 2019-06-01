#include "Mouse.h"
#include "GameWindow.h"

glm::dvec2 Mouse::GetPosition()
{
	return glm::dvec2();
}

glm::dvec2 Mouse::GetPosition(GameWindow* window)
{
	glm::dvec2 position;
	glfwGetCursorPos(window->GetHandle(), &position.x, &position.y);
	return position;
}

void Mouse::SetPosition(glm::dvec2 position, GameWindow* window)
{
	glfwSetCursorPos(window->GetHandle(), position.x, position.y);
}
