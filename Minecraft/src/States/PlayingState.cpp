#include "PlayingState.h"
#include "../Game.h"
#include "../World/Event/PlayerDigEvent.h"
#include "../Util/Ray.h"
#include "../Input/Mouse.h"
#include "../Util/Stopwatch.h"

PlayingState::PlayingState(Game& game): GameState(game), mWorld(mGame->getCamera())
{
	mPlayer.position = { 0.f, 6.5f, 0.f };
	mPlayer.rotation.y = 120.f;

	mGame->getCamera().bindEntity(mPlayer);
}

void PlayingState::update(double deltaTime)
{
	mPlayer.handleInput(*mGame->getWindow());

	static Stopwatch stopwatch;

	glm::vec3 lastPosition;

	for (Ray ray({ mPlayer.position.x, mPlayer.position.y + 0.6f, mPlayer.position.z }, mPlayer.rotation);
		ray.getLength() < 6;
		ray.step(0.05))
	{
		const auto rayEnd = ray.getEnd();

		auto block = mWorld.getBlock(rayEnd.x, rayEnd.y, rayEnd.z);

		if (stopwatch.elapsedTime() > 0.2)
		{
			if (block != BlockId::Air)
			{
				stopwatch.start();
				if (Mouse::isButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
				{
					mWorld.addEvent<PlayerDigEvent>(mPlayer, ray.getEnd(), BlockId::Air);
					break;
				}

				else if (Mouse::isButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
				{
					//stopwatch.start();
					mWorld.addEvent<PlayerDigEvent>(mPlayer, lastPosition, BlockId::WhiteWool);
					break;
				}
			}
		}
		lastPosition = ray.getEnd();
	}

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
