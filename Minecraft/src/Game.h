#pragma once

#include <GLFW/glfw3.h>

#include "Camera.h"
#include "World/World.h"

class Game
{
public:
	Game();
	~Game();

	void Run();
private:
	GLFWwindow* m_window = nullptr;

	Camera m_camera;
	World m_world;
};

