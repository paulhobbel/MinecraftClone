#pragma once

#include "Chuck/ChuckProvider.h"

class World
{
public:
	World();
	~World();

	ChuckProvider& GetChunkProvider();

private:
	ChuckProvider m_chunkProvider;
};

