#pragma once

#include "../Renderer/MainRenderer.h"

class Game;

class GameState
{
public:
	GameState(Game& game);
	virtual ~GameState() = default;

	virtual void update(double deltaTime) = 0;
	virtual void render(MainRenderer& renderer) = 0;

	virtual void onOpen();

protected:
	Game* mGame;
};
