#pragma once

#include "../../Math/Vec2.h"

class World;
class ChunkRenderer;

class Chunk
{
public:
	Chunk(World& world, const Vec2& position);

	Vec2& GetPosition();
	void Render(ChunkRenderer& renderer);

private:
	World* m_world;

	Vec2 m_position;
};

