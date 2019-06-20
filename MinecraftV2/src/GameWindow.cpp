#include <iostream>

#include "GameWindow.h"

GameWindow::GameWindow(int width, int height, const std::string& title)
{
	if (!glfwInit())
		exit(EXIT_FAILURE);

	mHandle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

	if (mHandle == nullptr)
		exit(EXIT_FAILURE);

	// Create pointer to self
	glfwSetWindowUserPointer(mHandle, this);

	// Set key callback
	glfwSetKeyCallback(mHandle, [](GLFWwindow * handle, int key, int scanCode, int action, int mods) {
		auto& self = *static_cast<GameWindow*>(glfwGetWindowUserPointer(handle));

		self.onInput(key, scanCode, action, mods);
	});

	glfwSetMouseButtonCallback(mHandle, [](GLFWwindow* handle, int button, int action, int mods) {
		auto& self = *static_cast<GameWindow*>(glfwGetWindowUserPointer(handle));

		self.onMouseButton(button, action);
		});

	glfwSetWindowFocusCallback(mHandle, [](GLFWwindow * handle, int flag) {
		auto& self = *static_cast<GameWindow*>(glfwGetWindowUserPointer(handle));

		self.onFocus(flag == GLFW_TRUE);
	});

	// Set resize callback
	glfwSetWindowSizeCallback(mHandle, [](GLFWwindow* handle, int width, int height) {
		auto& self = *static_cast<GameWindow*>(glfwGetWindowUserPointer(handle));

		self.onResize(width, height);
	});

	glfwSetErrorCallback([](int errorCode, const char* description) {
		std::cout << "[ERROR/GameWindow] code: " << errorCode << ", description: " << description << std::endl;
	});

	glfwFocusWindow(mHandle);
	mFocused = true;
}

GameWindow::~GameWindow()
{
	glfwTerminate();
}

bool GameWindow::initialized() const
{
	return mHandle != nullptr;
}

bool GameWindow::isOpen() const
{
	return glfwWindowShouldClose(mHandle);
}

void GameWindow::setTitle(const std::string& title) const
{
	glfwSetWindowTitle(mHandle, title.c_str());
}

void GameWindow::setSize(int width, int height) const
{
	glfwSetWindowSize(mHandle, width, height);
}

bool GameWindow::hasFocus() const
{
	return mFocused;
}

GLFWwindow* GameWindow::getHandle() const
{
	return mHandle;
}

glm::ivec2 GameWindow::getSize() const
{
	glm::ivec2 size(0, 0);
	glfwGetWindowSize(mHandle, &size.x, &size.y);
	return size;
}

void GameWindow::setMouseCursorVisible(bool flag) const
{
	glfwSetInputMode(mHandle, GLFW_CURSOR, flag ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN);
}

void GameWindow::setResizeCallback(std::function<void(glm::vec2)> callback)
{
	mResizeCb = callback;
}

void GameWindow::setInputCallback(std::function<void(int key, int scanCode, int action, int mods)> callback)
{
	mInputCb = callback;
}

void GameWindow::setMouseButtonCallback(std::function<void(int, int)> callback)
{
	mMouseCb = callback;
}

void GameWindow::setGLContext() const
{
	std::cout << "[INFO/GameWindow] Initializing OpenGL" << std::endl;
	glfwMakeContextCurrent(mHandle);
	gladLoadGL();
	//gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
	std::cout << "[INFO/GameWindow] OpenGL Loaded, using: " << glGetString(GL_VERSION)  << std::endl;
}

void GameWindow::swapBuffers() const
{
	glfwSwapBuffers(mHandle);
}

void GameWindow::onResize(int width, int height) const
{
	glViewport(0, 0, width, height);

	if (mResizeCb)
		mResizeCb({ width, height });
}

void GameWindow::onFocus(bool focussed)
{
	mFocused = focussed;
}

void GameWindow::onInput(int key, int scanCode, int action, int mods) const
{
	//std::cout << "[INFO/GameWindow] Got input { key: " << key << ", scanCode: " << scanCode << ", action: " << action << ", mods: " << mods << " }" << std::endl;

	if (mInputCb)
		mInputCb(key, scanCode, action, mods);

}

void GameWindow::onMouseButton(int button, int state)
{
	if (mMouseCb)
		mMouseCb(button, state);
}
