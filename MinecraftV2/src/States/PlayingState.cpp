#include "PlayingState.h"
#include "../Game.h"

PlayingState::PlayingState(Game& game): GameState(game), mWorld(mGame->getCamera())
{
	mPlayer.position = { 0.f, 6.5f, 0.f };
	mPlayer.rotation.y = 120.f;

	mGame->getCamera().bindEntity(mPlayer);
}

void PlayingState::update(double deltaTime)
{
	mPlayer.handleInput(*mGame->getWindow());
	mPlayer.update(deltaTime, mWorld);
	mWorld.update(mGame->getCamera());
}

void PlayingState::render(MainRenderer& renderer)
{
	mWorld.render(renderer, mGame->getCamera());
}

void PlayingState::onOpen()
{
	mGame->getWindow()->setMouseCursorVisible(false);
}
