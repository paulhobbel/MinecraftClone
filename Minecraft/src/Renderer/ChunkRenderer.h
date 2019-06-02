#pragma once

#include <vector>

#include "../Shader/ChunkShader.h"
#include "../Initializable.h"

class Camera;
class ChunkMesh;
struct RenderInfo;

class ChunkRenderer : public Initializable
{
public:
	ChunkRenderer();

	void Init() override;

	void AddMesh(const ChunkMesh& mesh);
	void Render(Camera& camera);
private:
	std::vector<const RenderInfo*> m_chunks;

	ChunkShader m_shader;
};

