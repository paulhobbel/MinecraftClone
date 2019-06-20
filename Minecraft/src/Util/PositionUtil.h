#pragma once

#include <glm/vec3.hpp>

class PositionUtil
{
public:
	static glm::ivec3 worldToChunkPosition(int x, int y, int z);
	static glm::ivec3 worldToBlockPosition(int x, int y, int z);

	static glm::ivec3 sectionToWorldBlockPosition(glm::ivec3 sectionPosition, int x, int y, int z);
};