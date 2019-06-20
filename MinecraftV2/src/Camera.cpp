#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"

Camera::Camera()
{
	mProjectionMatrix = glm::perspective(glm::radians(60.f), (float)1280.f / (float)720.f, .1f, 2000.f);
	mViewMatrix = glm::mat4();
	mProjViewMatrix = glm::mat4();
}

void Camera::bindEntity(const Entity& entity) noexcept
{
	mEntity = &entity;
}

void Camera::setPerspective(glm::vec2 size) noexcept
{
	mProjectionMatrix = glm::perspective(glm::radians(60.f), size.x / size.y, .1f, 2000.f);
}

void Camera::update() noexcept
{
	position = { mEntity->position.x, mEntity->position.y + 0.6f, mEntity->position.z };
	rotation = mEntity->rotation;

	//std::cout << "Chunk: " << position.x / CHUNK_SIZE << " " << position.z / CHUNK_SIZE << ", Position: " << glm::to_string(position) << ", rotation: " << glm::to_string(rotation) << std::endl;

	mViewMatrix = glm::mat4(1.f);

	mViewMatrix = glm::rotate(mViewMatrix, glm::radians(rotation.x), { 1, 0, 0 });
	mViewMatrix = glm::rotate(mViewMatrix, glm::radians(rotation.y), { 0, 1, 0 });
	mViewMatrix = glm::rotate(mViewMatrix, glm::radians(rotation.z), { 0, 0, 1 });

	mViewMatrix = glm::translate(mViewMatrix, -position);

	mProjViewMatrix = mProjectionMatrix * mViewMatrix;

	mFrustum.update(mProjViewMatrix);
}

glm::mat4& Camera::getProjectionMatrix()
{
	return mProjectionMatrix;
}

glm::mat4& Camera::getViewMatrix()
{
	return mViewMatrix;
}

const glm::mat4& Camera::getProjectionViewMatrix() const
{
	return mProjViewMatrix;
}

const ViewFrustum& Camera::getFrustum() const noexcept
{
	return mFrustum;
}
