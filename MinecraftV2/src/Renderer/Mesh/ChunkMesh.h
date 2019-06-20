#pragma once

#include <glm/vec3.hpp>
#include "Mesh.h"
#include "../../World/Block/BlockFace.h"

struct Block;
class ChunkSection;

class ChunkMesh : public Mesh
{
public:
	void setHasBuffered(bool flag);
	bool hasBuffered() const;

	class Builder
	{
	public:
		Builder(ChunkSection& section, ChunkMesh& mesh);

		void build();

	private:
		void tryAddFace(BlockFace face, glm::vec3 blockPosition, glm::vec3 blockFacing);
		bool shouldMakeFace(const glm::ivec3& blockPosition, const Block& block);

		ChunkSection* mSection;
		ChunkMesh* mMesh;
		const Block* mBlock = nullptr;
	};

private:
	void addFace(BlockFace face, glm::vec3 chunkPosition, glm::vec3 blockPosition);

	bool mBuffered = true;

	unsigned int mIndiceIndex = 0;
};
