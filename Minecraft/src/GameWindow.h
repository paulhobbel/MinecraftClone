#pragma once

#include <string>
#include <vector>
#include <functional>
#include <glm/vec2.hpp>
#include <GLFW/glfw3.h>

class GameWindow
{
public:
	GameWindow(int width, int height, std::string title);

	bool Initialized();

	bool IsOpen();
	void SetTitle(std::string title);
	void SetSize(int width, int height);

	GLFWwindow* GetHandle();
	glm::ivec2 GetSize();

	void SetInputCallback(std::function<void(int, int, int, int)> callback);

	void SetGLContext();
	void SwapBuffers();

private:

	std::function<void(int key, int scanCode, int action, int mods)> m_inputCb;

	void OnResize(int width, int height);
	void OnInput(int key, int scanCode, int action, int mods);

	GLFWwindow* m_handle;
};