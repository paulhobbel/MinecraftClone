#pragma once

#include <glm/vec3.hpp>

struct AABB
{
	AABB(const glm::vec3& dim)
		: dimensions(dim)
	{
	}

	void Update(const glm::vec3& position);

	glm::vec3 getVN(const glm::vec3& normal) const;

	glm::vec3 getVP(const glm::vec3& normal) const;

	glm::vec3 position;
	const glm::vec3 dimensions;
};