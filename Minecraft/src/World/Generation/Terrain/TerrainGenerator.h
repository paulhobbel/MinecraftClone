#pragma once

class Chunk;

class TerrainGenerator
{
public:
	virtual void GenerateTerrain(Chunk& chunk) = 0;
	virtual ~TerrainGenerator() = default;
};