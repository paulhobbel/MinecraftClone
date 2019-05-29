#pragma once

#include "TerrainGenerator.h"

class FlatTerrainGenerator : public TerrainGenerator
{
public:
	void GenerateTerrain(Chunk& chunk) override;
};