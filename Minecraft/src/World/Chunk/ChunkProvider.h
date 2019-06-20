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

	std::unordered_map<glm::ivec2, std::shared_ptr<Chunk>>& getChunks();
	Chunk& getChunk(int x, int y);

	bool makeMesh(int x, int z, const Camera& camera);

	bool chunkExists(int x, int y) const;
	void loadChunk(int x, int y);

private:
	World* mWorld;
	TerrainGenerator* mGenerator;

	std::unordered_map<glm::ivec2, std::shared_ptr<Chunk>> mChunks;
};

