#include "LoadingState.h"
#include "../Game.h"

LoadingState::LoadingState(Game& game) : GameState(game)
{
}

void LoadingState::update(double deltaTime)
{

}

void LoadingState::render(MainRenderer& renderer)
{
}

void LoadingState::onOpen()
{
	auto resourceManager = mGame->getResourceManager();
	resourceManager->loadBlocks();
	resourceManager->loadBlockTextures();

	mGame->getWindow()->setGLContext();

	resourceManager->uploadBlockAtlas();
}
