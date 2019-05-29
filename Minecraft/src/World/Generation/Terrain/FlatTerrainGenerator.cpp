#include "FlatTerrainGenerator.h"
#include "../../Chunk/Chunk.h"
#include "../../Block/BlockId.h"

void FlatTerrainGenerator::GenerateTerrain(Chunk& chunk)
{
	for (int x = 0; x < 16; x++)
	{
		for (int z = 0; z < 16; z++)
		{
			chunk.SetBlock(x, 0, z, BlockId::Stone);
			chunk.SetBlock(x, 1, z, BlockId::Dirt);
			chunk.SetBlock(x, 2, z, BlockId::Dirt);
			chunk.SetBlock(x, 3, z, BlockId::Dirt);
			chunk.SetBlock(x, 4, z, BlockId::Grass);
		}
	}
}
