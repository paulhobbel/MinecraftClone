#pragma once

#include <unordered_map>

#include "../../Math/Vec2.h"
#include "Chunk.h"

class World;

class ChuckProvider
{
public:
	ChuckProvider(World& world);
	~ChuckProvider();

	Chunk& GetChunk(int x, int y);
	bool ChunkExists(int x, int y) const;

private:
	World* m_world;

	std::unordered_map<Vec2, Chunk> m_chunks;
};

