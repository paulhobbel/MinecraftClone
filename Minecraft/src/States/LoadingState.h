#pragma once
#include "GameState.h"

class LoadingState : public GameState
{
public:
	LoadingState(Game& game);

	void update(double deltaTime) override;
	void render(MainRenderer& renderer) override;
	void onOpen() override;
};
