#include <iostream>

#include "GameWindow.h"

GameWindow::GameWindow(int width, int height, std::string title)
{
	m_handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

	// Create pointer to self
	glfwSetWindowUserPointer(m_handle, this);

	// Set key callback
	glfwSetKeyCallback(m_handle, [](GLFWwindow * handle, int key, int scanCode, int action, int mods) {
		auto& self = *static_cast<GameWindow*>(glfwGetWindowUserPointer(handle));

		self.OnInput(key, scanCode, action, mods);
	});

	glfwSetWindowFocusCallback(m_handle, [](GLFWwindow * handle, int flag) {
		auto& self = *static_cast<GameWindow*>(glfwGetWindowUserPointer(handle));

		self.OnFocus(flag == GLFW_TRUE);
	});

	// Set resize callback
	glfwSetWindowSizeCallback(m_handle, [](GLFWwindow* handle, int width, int height) {
		auto& self = *static_cast<GameWindow*>(glfwGetWindowUserPointer(handle));

		self.OnResize(width, height);
	});

	glfwSetErrorCallback([](int errorCode, const char* description) {
		std::cout << "[ERROR/GameWindow] code: " << errorCode << ", description: " << description << std::endl;
	});

	glfwFocusWindow(m_handle);
	m_focused = true;
}

bool GameWindow::Initialized()
{
	return m_handle != nullptr;
}

bool GameWindow::IsOpen()
{
	return glfwWindowShouldClose(m_handle);
}

void GameWindow::SetTitle(std::string title)
{
	glfwSetWindowTitle(m_handle, title.c_str());
}

void GameWindow::SetSize(int width, int height)
{
	glfwSetWindowSize(m_handle, width, height);
}

bool GameWindow::HasFocus()
{
	return m_focused;
}

GLFWwindow* GameWindow::GetHandle()
{
	return m_handle;
}

glm::ivec2 GameWindow::GetSize()
{
	glm::ivec2 size(0, 0);
	glfwGetWindowSize(m_handle, &size.x, &size.y);
	return size;
}

void GameWindow::SetResizeCallback(std::function<void(glm::vec2)> callback)
{
	m_resizeCb = callback;
}

void GameWindow::SetInputCallback(std::function<void(int key, int scanCode, int action, int mods)> callback)
{
	m_inputCb = callback;
}

void GameWindow::SetGLContext()
{
	glfwMakeContextCurrent(m_handle);
	gladLoadGL();
	//gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
}

void GameWindow::SwapBuffers()
{
	glfwSwapBuffers(m_handle);
}

void GameWindow::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);

	if (m_resizeCb)
		m_resizeCb({ width, height });
}

void GameWindow::OnFocus(bool focussed)
{
	m_focused = focussed;
}

void GameWindow::OnInput(int key, int scanCode, int action, int mods)
{
	//std::cout << "[INFO/GameWindow] Got input { key: " << key << ", scanCode: " << scanCode << ", action: " << action << ", mods: " << mods << " }" << std::endl;

	if (m_inputCb)
		m_inputCb(key, scanCode, action, mods);

}
