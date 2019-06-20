#pragma once
#include "../Camera.h"
#include "Mesh/ChunkMesh.h"
#include "Shader/ChunkShader.h"
#include "Texture/SimpleTexture.h"

class ResourceManager;
class AtlasTexture;

class ChunkRenderer
{
public:
	void init(const ResourceManager& resourceManager);

	//void compileChunkSection(ChunkSection& )
	void addMesh(const ChunkMesh& mesh);
	void render(const Camera& camera);

private:
	std::vector<const ChunkMesh*> mChunks;
	ChunkShader mShader;
	AtlasTexture* mTexture;
	SimpleTexture testTexture;
};
