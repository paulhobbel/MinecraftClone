#pragma once

#include <vector>

class ChunkMesh;
class ChunkRenderer
{
public:
	void Add(ChunkMesh& mesh);
	void Render();
private:
	std::vector<ChunkMesh> m_chunks;
};

