#pragma once

#include "Chunk/ChunkProvider.h"

class World
{
public:
	World();
	~World();

	ChunkProvider& GetChunkProvider();

private:
	ChunkProvider m_chunkProvider;
};

