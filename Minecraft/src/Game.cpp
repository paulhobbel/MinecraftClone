#include <iostream>
#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

	//m_camera.position.x = -5;
	m_camera.position.z = -20;
	m_camera.rotation.y = 0;
	m_camera.rotation.x = 5;
	//m_camera.rotation.z = 45;

	m_window->SetInputCallback([this](int key, int scanCode, int action, int mods) {
		switch (key)
		{
		case GLFW_KEY_W:
			m_camera.position.z += 1;
			break;
		case GLFW_KEY_S:
			m_camera.position.z -= 1;
			break;
		case GLFW_KEY_A:
			m_camera.position.x += 1;
			break;
		case GLFW_KEY_D:
			m_camera.position.x -= 1;
			break;
		default:
			break;
		}
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
		/* Render here */
		m_renderer.Render(m_camera);

		/* Swap front and back buffers */
		m_window->SwapBuffers();

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
}

World& Game::GetWorld()
{
	return m_world;
}
