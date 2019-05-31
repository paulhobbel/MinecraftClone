#pragma once

#include <vector>

#include "../Shader/ChunkShader.h"

class Camera;
class ChunkMesh;

class ChunkRenderer
{
public:
	ChunkRenderer();

	void Add(const ChunkMesh& mesh);
	void Render(Camera& camera);
private:
	std::vector<ChunkMesh> m_chunks;

	//ChunkShader m_shader;
};

