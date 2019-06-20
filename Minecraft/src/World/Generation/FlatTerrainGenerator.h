#pragma once
#include "TerrainGenerator.h"

class FlatTerrainGenerator : public TerrainGenerator
{
public:
	void generateTerrain(Chunk& chunk) override;
};
