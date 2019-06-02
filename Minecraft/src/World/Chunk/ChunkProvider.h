#pragma once

#include <unordered_map>
#include "glm/gtx/hash.hpp"
#include <glm/vec2.hpp>

#include "Chunk.h"

class Camera;
class World;

class ChunkProvider
{
public:
	ChunkProvider(World& world);
	~ChunkProvider();

	std::unordered_map<glm::ivec2, Chunk>& GetChunks();
	Chunk& GetChunk(int x, int y);

	bool MakeMesh(int x, int z, const Camera& camera);

	bool ChunkExists(int x, int y) const;
	void LoadChunk(int x, int y);

private:
	World* m_world;
	TerrainGenerator* m_generator;

	std::unordered_map<glm::ivec2, Chunk> m_chunks;
};

