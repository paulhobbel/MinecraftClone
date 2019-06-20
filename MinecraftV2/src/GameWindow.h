#pragma once

#include <string>
#include <functional>
#include <glm/vec2.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class GameWindow
{
public:
	GameWindow(int width, int height, const std::string& title);
	~GameWindow();

	bool initialized() const;

	bool isOpen() const;
	void setTitle(const std::string& title) const;
	void setSize(int width, int height) const;

	bool hasFocus() const;

	GLFWwindow* getHandle() const;
	glm::ivec2 getSize() const;

	void setMouseCursorVisible(bool flag) const;

	void setResizeCallback(std::function<void(glm::vec2)> callback);
	void setInputCallback(std::function<void(int, int, int, int)> callback);

	void setGLContext() const;
	void swapBuffers() const;

private:
	bool mFocused;
	std::function<void(glm::vec2 size)> mResizeCb;
	std::function<void(int key, int scanCode, int action, int mods)> mInputCb;

	void onResize(int width, int height) const;
	void onFocus(bool focussed);
	void onInput(int key, int scanCode, int action, int mods) const;

	GLFWwindow* mHandle;
};