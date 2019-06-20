#pragma once

#include <glm/vec3.hpp>

class PositionUtilities
{
public:
	static glm::ivec3 WorldToChunkPosition(int x, int y, int z);
	static glm::ivec3 WorldToBlockPosition(int x, int y, int z);

	static glm::ivec3 SectionToWorldBlockPosition(glm::ivec3 sectionPosition, int x, int y, int z);
};