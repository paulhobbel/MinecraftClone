#pragma once
#include <glm/vec3.hpp>

class Ray
{
public:
	Ray(const glm::vec3& position, const glm::vec3& direction);

	void step(float scale);

	const glm::vec3& getEnd() const;

	float getLength() const;

private:
	glm::vec3 mRayStart;
	glm::vec3 mRayEnd;
	glm::vec3 mDirection;
};
