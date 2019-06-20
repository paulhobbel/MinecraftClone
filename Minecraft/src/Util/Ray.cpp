#include "Ray.h"
#include <glm/detail/func_trigonometric.inl>
#include <glm/detail/func_geometric.inl>

Ray::Ray(const glm::vec3& position, const glm::vec3& direction) :
	mRayStart(position), mRayEnd(position), mDirection(direction)
{
}

void Ray::step(float scale)
{
	float yaw = glm::radians(mDirection.y + 90);
	float pitch = glm::radians(mDirection.x);

	auto& p = mRayEnd;

	p.x -= glm::cos(yaw) * scale;
	p.z -= glm::sin(yaw) * scale;
	p.y -= glm::tan(pitch) * scale;
}

const glm::vec3& Ray::getEnd() const
{
	return mRayEnd;
}

float Ray::getLength() const
{
	return glm::distance(mRayStart, mRayEnd);
}