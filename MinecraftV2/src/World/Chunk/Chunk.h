#pragma once

#include <vector>
#include <glm/vec2.hpp>

#include "../Block/Block.h"
#include "ChunkSection.h"

class World;
class Camera;
class MainRenderer;
class TerrainGenerator;

class Chunk
{
public:
	Chunk() = default;
	Chunk(World& world, const glm::ivec2& position);

	Block getBlock(int x, int y, int z) const noexcept;
	void setBlock(int x, int y, int z, Block block);
	bool isLoaded() const noexcept;

	ChunkSection& getSection(int index);
	glm::ivec2& getPosition();

	void load(TerrainGenerator& generator);

	bool makeMesh(const Camera& camera);

	void render(MainRenderer& renderer, const Camera& camera);

private:
	void addSection();
	void addSectionsBlockTarget(int blockY);
	void addSectionsIndexTarget(int index);
	bool outOfBounds(int x, int y, int z) const noexcept;

	bool mLoaded = false;

	std::vector<std::shared_ptr<ChunkSection>> mSections;
	glm::ivec2 mPosition;

	World* mWorld;
};

