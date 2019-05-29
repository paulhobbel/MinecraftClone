#pragma once

#include <unordered_map>

#include "../../Math/Vec2.h"
#include "Chunk.h"

class World;

class ChunkProvider
{
public:
	ChunkProvider(World& world);
	~ChunkProvider();

	Chunk& GetChunk(int x, int y);
	bool ChunkExists(int x, int y) const;
	void LoadChunk(int x, int y);

private:
	World* m_world;
	TerrainGenerator* m_generator;

	std::unordered_map<Vec2, Chunk> m_chunks;
};

