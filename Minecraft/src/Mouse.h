#pragma once

#include <glm/vec2.hpp>

class GameWindow;

class Mouse
{
public:
	static glm::dvec2 GetPosition();
	static glm::dvec2 GetPosition(GameWindow* window);
	static void SetPosition(glm::dvec2 position, GameWindow* window);
};