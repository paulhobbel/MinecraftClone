#pragma once

#include <string>
#include <vector>
#include <functional>
#include <glm/vec2.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class GameWindow
{
public:
	GameWindow(int width, int height, std::string title);

	bool Initialized();

	bool IsOpen();
	void SetTitle(std::string title);
	void SetSize(int width, int height);

	bool HasFocus();

	GLFWwindow* GetHandle();
	glm::ivec2 GetSize();

	void SetResizeCallback(std::function<void(glm::vec2)> callback);
	void SetInputCallback(std::function<void(int, int, int, int)> callback);

	void SetGLContext();
	void SwapBuffers();

private:
	bool m_focused;
	std::function<void(glm::vec2 size)> m_resizeCb;
	std::function<void(int key, int scanCode, int action, int mods)> m_inputCb;

	void OnResize(int width, int height);
	void OnFocus(bool focussed);
	void OnInput(int key, int scanCode, int action, int mods);

	GLFWwindow* m_handle;
};