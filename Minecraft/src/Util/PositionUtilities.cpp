#include "PositionUtilities.h"
#include "../Constants.h"

glm::ivec3 PositionUtilities::WorldToChunkPosition(int x, int y, int z)
{
	return glm::ivec3(x / CHUNK_SIZE, y, z / CHUNK_SIZE);
}

glm::ivec3 PositionUtilities::WorldToBlockPosition(int x, int y, int z)
{
	return glm::ivec3(x % CHUNK_SIZE, y, z % CHUNK_SIZE);
}

glm::ivec3 PositionUtilities::SectionToWorldBlockPosition(glm::ivec3 sectionPosition, int x, int y, int z)
{
	return glm::ivec3(
		sectionPosition.x * CHUNK_SIZE + x,
		sectionPosition.y * CHUNK_SIZE + y,
		sectionPosition.z * CHUNK_SIZE + z
	);
}
