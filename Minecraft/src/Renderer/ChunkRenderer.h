#pragma once

#include <vector>

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
};

