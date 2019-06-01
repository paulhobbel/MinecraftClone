#pragma once

#include <vector>

#include "../Shader/ChunkShader.h"
#include "../Initializable.h"

class Camera;
class ChunkMesh;

class ChunkRenderer : public Initializable
{
public:
	ChunkRenderer();

	void Init() override;

	void Add(const ChunkMesh& mesh);
	void Render(Camera& camera);
private:
	std::vector<ChunkMesh> m_chunks;

	ChunkShader m_shader;
};

