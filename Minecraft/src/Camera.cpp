#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"
#include "GameWindow.h"
#include "Keyboard.h"
#include "Mouse.h"

Camera::Camera()
{
	m_projectionMatrix = glm::perspective(glm::radians(60.f), (float) 1280.f / (float) 720.f, .1f, 2000.f);
	m_viewMatrix = glm::mat4();
	m_projViewMatrix = glm::mat4();
}

void Camera::BindEntity(const Entity& entity) noexcept
{
	m_entity = &entity;
}

void Camera::SetPerspective(glm::vec2 size) noexcept
{
	m_projectionMatrix = glm::perspective(glm::radians(60.f), size.x / size.y, .1f, 2000.f);
}

void Camera::Update() noexcept
{
	position = { m_entity->position.x, m_entity->position.y + 0.6f, m_entity->position.z };
	rotation = m_entity->rotation;

	//std::cout << "position: " << glm::to_string(position) << ", rotation: " << glm::to_string(rotation) << std::endl;

	m_viewMatrix = glm::mat4(1.f);

	m_viewMatrix = glm::rotate(m_viewMatrix, glm::radians(rotation.x), { 1, 0, 0 });
	m_viewMatrix = glm::rotate(m_viewMatrix, glm::radians(rotation.y), { 0, 1, 0 });
	m_viewMatrix = glm::rotate(m_viewMatrix, glm::radians(rotation.z), { 0, 0, 1 });

	m_viewMatrix = glm::translate(m_viewMatrix, -position);

	m_projViewMatrix = m_projectionMatrix * m_viewMatrix;

	m_frustum.Update(m_projViewMatrix);
}

glm::mat4& Camera::getProjectionMatrix()
{
	return m_projectionMatrix;
}

glm::mat4& Camera::getViewMatrix()
{
	return m_viewMatrix;
}

glm::mat4& Camera::getProjectionViewMatrix()
{
	return m_projViewMatrix;
}

const ViewFrustum& Camera::getFrustum() const noexcept
{
	return m_frustum;
}
