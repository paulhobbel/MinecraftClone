#pragma once

#include <vector>

class Camera;
class ChunkMesh;

class ChunkRenderer
{
public:
	void Add(const ChunkMesh& mesh);
	void Render(const Camera& camera);
private:
	std::vector<ChunkMesh> m_chunks;
};

