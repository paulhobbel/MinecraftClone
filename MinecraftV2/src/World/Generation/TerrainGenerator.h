#pragma once
class Chunk;

class TerrainGenerator
{
public:
	virtual void generateTerrain(Chunk& chunk) = 0;
	virtual ~TerrainGenerator() = default;
};