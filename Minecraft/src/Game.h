#pragma once

#include <GLFW/glfw3.h>

class Game
{
public:
	Game();
	~Game();

	void Run();
private:
	GLFWwindow* m_window = nullptr;
};

