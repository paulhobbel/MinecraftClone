#include "PlayerDigEvent.h"
#include "../../Util/PositionUtil.h"
#include "../World.h"

PlayerDigEvent::PlayerDigEvent(Player& player, const glm::vec3& location, Block block): mPlayer(&player), mDigPosition(location), mBlock(block)
{
}

void PlayerDigEvent::handle(World& world)
{
	auto chunkPosition = PositionUtil::worldToChunkPosition(mDigPosition.x, mDigPosition.y, mDigPosition.z);
	if(world.getChunkProvider().getChunk(chunkPosition.x, chunkPosition.z).isLoaded())
	{
		dig(world);
	}
}

void PlayerDigEvent::dig(World& world)
{
	auto block = world.getBlock(mDigPosition.x, mDigPosition.y, mDigPosition.z);

	world.updateChunk(mDigPosition.x, mDigPosition.y, mDigPosition.z);
	world.setBlock(mDigPosition.x, mDigPosition.y, mDigPosition.z, mBlock);
}
