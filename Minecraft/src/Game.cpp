#include "Game.h"

#include "GLFW/glfw3.h"

Game::Game()
{
	if (!glfwInit())
		return;
	//exit(-1);

	m_window = glfwCreateWindow(1280, 720, "Minecraft", NULL, NULL);

	if (!m_window)
	{
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_window);
}

Game::~Game()
{
	glfwTerminate();
}

void Game::Run()
{
	int width, height;
	glfwGetWindowSize(m_window, &width, &height);

	glViewport(0, 0, width, height);

	while (!glfwWindowShouldClose(m_window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(m_window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
}
