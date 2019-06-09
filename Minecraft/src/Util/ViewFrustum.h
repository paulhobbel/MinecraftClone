#pragma once

#include <array>
#include <glm/matrix.hpp>
#include <glm/vec3.hpp>

struct AABB;

struct Plane
{
	float DistanceToPoint(const glm::vec3& point) const;

	float distanceToOrigin;
	glm::vec3 normal;
};

class ViewFrustum
{
public:
	void Update(const glm::mat4& projViewMatrix) noexcept;

	bool IsBoxInFrustum(const AABB& box) const noexcept;

private:
	std::array<Plane, 6> m_planes;
};