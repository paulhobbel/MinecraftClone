#pragma once

#include <glm/vec3.hpp>

#include "AABB.h"

struct Entity
{
	Entity() :
		position(glm::vec3(0.f)),
		rotation(glm::vec3(0.f)),
		velocity(glm::vec3(0.f)),
		boundingBox({ 0.f, 0.f, 0.f })
	{}

	Entity(const glm::vec3& pos, const glm::vec3& rot) :
		position(pos),
		rotation(rot),
		velocity(glm::vec3(0.f)),
		boundingBox({ 0.f, 0.f, 0.f })
	{}

	Entity(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& box) :
		position(pos),
		rotation(rot),
		velocity(glm::vec3(0.f)),
		boundingBox(box)
	{}

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 velocity;

	AABB boundingBox;
};