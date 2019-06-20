#pragma once

#include <glm/vec2.hpp>

class GameWindow;

class Mouse
{
public:
	static glm::dvec2 getPosition();
	static glm::dvec2 getPosition(GameWindow* window);
	static void setPosition(glm::dvec2 position, GameWindow* window);
};