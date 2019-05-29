#pragma once

#include <glm/vec3.hpp>

struct Entity
{
	Entity() : 
		position(glm::vec3(0.f)),
		rotation(glm::vec3(0.f))
	{}

	Entity(const glm::vec3& pos, const glm::vec3& rot) :
		position(pos),
		rotation(rot)
	{}

	glm::vec3 position;
	glm::vec3 rotation;
};