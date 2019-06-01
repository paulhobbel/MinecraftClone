#include <iostream>
#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Keyboard.h"
#include "Game.h"

Game::Game() : m_world(m_camera)
{
	if (!glfwInit())
		exit(EXIT_FAILURE);
	

	m_window = new GameWindow(1280, 720, "Minecraft");

	if (!m_window->Initialized())
	{
		glfwTerminate();
		return;
	}

	m_window->SetGLContext();

	// Initialize everything that needs opengl
	m_renderer.Init();

	//m_camera.position.x = -5;
	m_camera.position.y = 1.5;
	m_camera.position.z = 3.5;
	//m_camera.rotation.y = 0;
	//m_camera.rotation.x = 5;
	//m_camera.rotation.z = 45;

	m_window->SetResizeCallback([this](glm::vec2 windowSize) {
		m_camera.SetPerspective(windowSize);
	});

	m_window->SetInputCallback([this](int key, int scanCode, int action, int mods) {
		Keyboard::UpdateKey(key, action);
	});
}

Game::~Game()
{
	glfwTerminate();
}

void Game::Run()
{
	/*int width, height;
	glfwGetWindowSize(m_window, &width, &height);

	glViewport(0, 0, width, height);*/

	while (!m_window->IsOpen())
	{
		m_camera.Update(m_window);

		/* Render here */
		m_renderer.Render(m_camera);

		/* Swap front and back buffers */
		m_window->SwapBuffers();

		//std::cout << glGetError() << std::endl;

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
}

World& Game::GetWorld()
{
	return m_world;
}
