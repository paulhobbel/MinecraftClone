#include <iostream>

#include "Input/Keyboard.h"
#include "Game.h"
#include "States/PlayingState.h"

//#include "World/Entities/Player.h"

Game::Game()
{
	std::cout << "[INFO/Game] Initializing game..." << std::endl;
	
	mResourceManager = std::make_shared<ResourceManager>();
	mWindow = std::make_shared<GameWindow>(1280, 720, "Minecraft");

	// Initialize everything that needs opengl
	//m_renderer.Init();

	mWindow->setResizeCallback([this](glm::vec2 windowSize) {
		//m_camera.SetPerspective(windowSize);
	});

	mWindow->setInputCallback([this](int key, int scanCode, int action, int mods) {
		Keyboard::updateKey(key, action);
	});

	mResourceManager->loadBlocks();
	mResourceManager->loadBlockTextures();

	mWindow->setGLContext();

	glEnable(GL_TEXTURE_2D);

	mResourceManager->uploadBlockAtlas();

	mRenderer.init(*mResourceManager);

	pushState<PlayingState>(*this);

	std::cout << "[INFO/Game] Done Initializing" << std::endl;
}

Game::~Game()
= default;

//Player player;

void Game::run()
{
	/*int width, height;
	glfwGetWindowSize(m_window, &width, &height);

	glViewport(0, 0, width, height);*/

	//Player player;

	//player.position = { 0.f, 6.5f, 0.f };
	//player.rotation.y = 120.f;

	//m_camera.BindEntity(player);

	auto lastFrame = glfwGetTime();

	while (!mWindow->isOpen() && !mStates.empty())
	{
		const auto currentFrame = glfwGetTime();
		const auto deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		auto& state = *mStates.back();

		state.update(deltaTime);
		state.render(mRenderer);
		mCamera.update();

		mRenderer.render(*mWindow, mCamera);

		//std::cout << glGetError() << std::endl;

		/* Poll for and process events */
		glfwPollEvents();


		if(mPopState)
		{
			mPopState = false;
			mStates.pop_back();
		}
	}

	std::cout << "[INFO/Game] Was fun having you here, see you next time." << std::endl;
}

std::shared_ptr<GameWindow> Game::getWindow() const
{
	return mWindow;
}

std::shared_ptr<ResourceManager> Game::getResourceManager() const
{
	return mResourceManager;
}

void Game::popState()
{
	mPopState = true;
}

Camera& Game::getCamera()
{
	return mCamera;
}
