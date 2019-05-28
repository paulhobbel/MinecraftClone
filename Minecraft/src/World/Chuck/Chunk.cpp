#include "Chunk.h"

Chunk::Chunk(World& world, const Vec2& position)
	: m_world(&world), m_position(position)
{
}

Vec2& Chunk::GetPosition()
{
	return m_position;
}
