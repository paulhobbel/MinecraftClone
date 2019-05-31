#pragma once

#include <vector>

#include "../../Math/Vec2.h"
#include "../Block/Block.h"
#include "ChunkSection.h"

class World;
class MainRenderer;
class TerrainGenerator;

class Chunk
{
public:
	Chunk() = default;
	Chunk(World& world, const Vec2& position);

	Block GetBlock(int x, int y, int z) const noexcept;
	void SetBlock(int x, int y, int z, Block block);
	bool IsLoaded() const noexcept;

	ChunkSection& GetSection(int index);
	Vec2& GetPosition();

	void Load(TerrainGenerator& generator);

	void MakeMesh();
	
	void Render(MainRenderer& renderer);

private:
	bool m_loaded = false;

	std::vector<ChunkSection> m_sections;
	Vec2 m_position;

	World* m_world;
};

