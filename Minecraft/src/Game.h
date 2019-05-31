#pragma once

#include "Camera.h"
#include "GameWindow.h"
#include "Renderer/MainRenderer.h"
#include "World/World.h"

class Game
{
public:
	Game();
	~Game();

	void Run();
	World& GetWorld();

private:
	GameWindow* m_window = nullptr;

	Camera m_camera;
	World m_world;

	MainRenderer m_renderer;
};

