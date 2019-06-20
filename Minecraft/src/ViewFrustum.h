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
	void update(const glm::mat4& projViewMatrix) noexcept;

	bool isBoxInFrustum(const AABB& box) const noexcept;

private:
	std::array<Plane, 6> mPlanes;
};