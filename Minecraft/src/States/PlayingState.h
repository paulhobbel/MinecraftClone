#pragma once
#include "GameState.h"

#include "../World/Entity/Player.h"
#include "../World/World.h"
#include "../Camera.h"

class PlayingState : public GameState
{
public:
	PlayingState(Game& game);

	void update(double deltaTime) override;
	void render(MainRenderer& renderer) override;
	void onOpen() override;

private:
	Player mPlayer;
	World mWorld;
};
