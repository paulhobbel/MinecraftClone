#pragma once

#include <vector>
#include <memory>
#include "GameWindow.h"
#include "States/GameState.h"
#include "Resources/ResourceManager.h"

#include "Camera.h"

class Game
{
public:
	Game();
	~Game();

	void run();

	std::shared_ptr<GameWindow> getWindow() const;
	std::shared_ptr<ResourceManager> getResourceManager() const;

	template<typename T, typename... Args>
	void pushState(Args&& ... args)
	{
		mStates.push_back(std::make_unique<T>(std::forward<Args>(args)...));
		auto& s = *mStates.back();
		s.onOpen();
	}

	void popState();

	Camera& getCamera();
	//World& GetWorld();

private:
	bool mPopState = { false };

	std::shared_ptr<GameWindow> mWindow;
	std::shared_ptr<ResourceManager> mResourceManager;

	std::vector<std::unique_ptr<GameState>> mStates;

	Camera mCamera;

	MainRenderer mRenderer;
};

