#include "ViewFrustum.h"
#include "AABB.h"

enum Planes
{
	Near,
	Far,
	Left,
	Right,
	Top,
	Bottom,
};

bool ViewFrustum::isBoxInFrustum(const AABB& box) const noexcept
{
	bool result = true;
	for (auto& plane : mPlanes)
	{
		if (plane.DistanceToPoint(box.getVP(plane.normal)) < 0)
		{
			return false;
		}
		
		if (plane.DistanceToPoint(box.getVN(plane.normal)) < 0)
		{
			result = true;
		}
	}
	return result;
}

void ViewFrustum::update(const glm::mat4& mat) noexcept
{
	// left
	mPlanes[Planes::Left].normal.x = mat[0][3] + mat[0][0];
	mPlanes[Planes::Left].normal.y = mat[1][3] + mat[1][0];
	mPlanes[Planes::Left].normal.z = mat[2][3] + mat[2][0];
	mPlanes[Planes::Left].distanceToOrigin = mat[3][3] + mat[3][0];

	// right
	mPlanes[Planes::Right].normal.x = mat[0][3] - mat[0][0];
	mPlanes[Planes::Right].normal.y = mat[1][3] - mat[1][0];
	mPlanes[Planes::Right].normal.z = mat[2][3] - mat[2][0];
	mPlanes[Planes::Right].distanceToOrigin = mat[3][3] - mat[3][0];

	// bottom
	mPlanes[Planes::Bottom].normal.x = mat[0][3] + mat[0][1];
	mPlanes[Planes::Bottom].normal.y = mat[1][3] + mat[1][1];
	mPlanes[Planes::Bottom].normal.z = mat[2][3] + mat[2][1];
	mPlanes[Planes::Bottom].distanceToOrigin = mat[3][3] + mat[3][1];

	// top
	mPlanes[Planes::Top].normal.x = mat[0][3] - mat[0][1];
	mPlanes[Planes::Top].normal.y = mat[1][3] - mat[1][1];
	mPlanes[Planes::Top].normal.z = mat[2][3] - mat[2][1];
	mPlanes[Planes::Top].distanceToOrigin = mat[3][3] - mat[3][1];

	// near
	mPlanes[Planes::Near].normal.x = mat[0][3] + mat[0][2];
	mPlanes[Planes::Near].normal.y = mat[1][3] + mat[1][2];
	mPlanes[Planes::Near].normal.z = mat[2][3] + mat[2][2];
	mPlanes[Planes::Near].distanceToOrigin = mat[3][3] + mat[3][2];

	// far
	mPlanes[Planes::Far].normal.x = mat[0][3] - mat[0][2];
	mPlanes[Planes::Far].normal.y = mat[1][3] - mat[1][2];
	mPlanes[Planes::Far].normal.z = mat[2][3] - mat[2][2];
	mPlanes[Planes::Far].distanceToOrigin = mat[3][3] - mat[3][2];

	for (auto& plane : mPlanes)
	{
		float length = glm::length(plane.normal);
		plane.normal /= length;
		plane.distanceToOrigin /= length;
	}
}

float Plane::DistanceToPoint(const glm::vec3& point) const
{
	return glm::dot(point, normal) + distanceToOrigin;
}
