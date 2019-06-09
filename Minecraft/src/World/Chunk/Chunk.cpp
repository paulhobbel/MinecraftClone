#include <glm/vec3.hpp>
#include "Chunk.h"
#include "../../Renderer/MainRenderer.h"
#include "../Generation/Terrain/TerrainGenerator.h"
#include "../../Camera.h"

Chunk::Chunk(World& world, const glm::ivec2& position)
	: m_world(&world), m_position(position)
{
}

Block Chunk::GetBlock(int x, int y, int z) const noexcept
{
	return Block();
}

void Chunk::SetBlock(int x, int y, int z, Block block)
{
	// Make sure enough sections are made
	int sIndex = (y / CHUNK_SIZE) + 1;

	while (m_sections.size() < sIndex)
	{
		int y = m_sections.size();
		m_sections.emplace_back(glm::ivec3(m_position.x, y, m_position.y), *m_world);
	}

	m_sections[y / CHUNK_SIZE].SetBlock(x, y % CHUNK_SIZE, z, block);
}

bool Chunk::IsLoaded() const noexcept
{
	return m_loaded;
}

void Chunk::Load(TerrainGenerator& generator)
{
	if (m_loaded)
		return;

	generator.GenerateTerrain(*this);

	m_loaded = true;
}

bool Chunk::MakeMesh(const Camera& camera)
{
	for (auto& section : m_sections)
	{
		if (!section.HasMesh() && camera.getFrustum().IsBoxInFrustum(section.m_aabb))
		{
			// Check if mesh wasn't already generated
			// Check if section is even visible
			section.MakeMesh();
			return true;
		}
	}
	return false;
}

void Chunk::Render(MainRenderer& renderer, const Camera& camera)
{
	for (auto& section : m_sections)
	{
		// Check if mesh is generated
		// Check if section is even visible

		if (!section.HasBuffered())
		{
			section.BufferMesh();
		}

		if(camera.getFrustum().IsBoxInFrustum(section.m_aabb))
			renderer.RenderChunk(section);
		//renderer.Add(section.GetMesh());
	}
}

ChunkSection& Chunk::GetSection(int index)
{
	// TODO: Add index out of bounds check

	return m_sections[index];
}

glm::ivec2& Chunk::GetPosition()
{
	return m_position;
}
