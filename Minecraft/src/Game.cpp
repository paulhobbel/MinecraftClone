#include <iostream>
#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Keyboard.h"
#include "Game.h"

#include "World/Entities/Player.h"

Game::Game() : m_world(m_camera)
{
	std::cout << "[INFO/Game] Initializing game..." << std::endl;

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

	m_window->SetResizeCallback([this](glm::vec2 windowSize) {
		m_camera.SetPerspective(windowSize);
	});

	m_window->SetInputCallback([this](int key, int scanCode, int action, int mods) {
		Keyboard::UpdateKey(key, action);
	});

	std::cout << "[INFO/Game] Done Initializing" << std::endl;
}

Game::~Game()
{
	glfwTerminate();
}

Player player;

void Game::Run()
{
	/*int width, height;
	glfwGetWindowSize(m_window, &width, &height);

	glViewport(0, 0, width, height);*/

	//Player player;

	player.position = { 0.f, 6.5f, 0.f };
	player.rotation.y = 120.f;

	m_camera.BindEntity(player);

	float lastFrame = static_cast<float>(glfwGetTime());

	while (!m_window->IsOpen())
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		float deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		player.HandleInput(m_window);
		player.Update(deltaTime, m_world);

		m_camera.Update();

		m_world.Render(m_renderer, m_camera);
		/* Render here */
		m_renderer.Render(m_camera);

		/* Swap front and back buffers */
		m_window->SwapBuffers();

		//std::cout << glGetError() << std::endl;

		/* Poll for and process events */
		glfwPollEvents();
	}

	std::cout << "[INFO/Game] Was fun having you here, see you next time." << std::endl;

	glfwTerminate();
}

World& Game::GetWorld()
{
	return m_world;
}
