#pragma once

#include <glm/vec2.hpp>
#include <map>

class GameWindow;

class Mouse
{
public:
	static void updateButton(int button, int state);
	static bool isButtonPressed(int button);
	static glm::dvec2 getPosition();
	static glm::dvec2 getPosition(GameWindow* window);
	static void setPosition(glm::dvec2 position, GameWindow* window);
private:
	static std::map<int, int> mButtons;
};