#pragma once

#include <vector>

#include "../Block/Block.h"
#include "ChunkSection.h"

#include <glm/vec2.hpp>

class World;
class MainRenderer;
class TerrainGenerator;

class Chunk
{
public:
	Chunk() = default;
	Chunk(World& world, const glm::ivec2& position);

	Block GetBlock(int x, int y, int z) const noexcept;
	void SetBlock(int x, int y, int z, Block block);
	bool IsLoaded() const noexcept;

	ChunkSection& GetSection(int index);
	glm::ivec2& GetPosition();

	void Load(TerrainGenerator& generator);

	bool MakeMesh();
	
	void Render(MainRenderer& renderer);

private:
	bool m_loaded = false;

	std::vector<ChunkSection> m_sections;
	glm::ivec2 m_position;

	World* m_world;
};

