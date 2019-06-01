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

void Camera::SetPerspective(glm::vec2 size) noexcept
{
	m_projectionMatrix = glm::perspective(glm::radians(60.f), size.x / size.y, .1f, 2000.f);
}

void Camera::Update(GameWindow* window) noexcept
{
	// Update camera position
	if (Keyboard::IsPressed(GLFW_KEY_W))
	{
		position.x += -glm::cos(glm::radians(rotation.y + 90)) * .2f;
		position.z += -glm::sin(glm::radians(rotation.y + 90)) * .2f;
	}

	if (Keyboard::IsPressed(GLFW_KEY_S))
	{
		position.x += glm::cos(glm::radians(rotation.y + 90)) * .2f;
		position.z += glm::sin(glm::radians(rotation.y + 90)) * .2f;
	}

	if (Keyboard::IsPressed(GLFW_KEY_A))
	{
		position.x += -glm::cos(glm::radians(rotation.y)) * .2f;
		position.z += -glm::sin(glm::radians(rotation.y)) * .2f;
	}

	if (Keyboard::IsPressed(GLFW_KEY_D))
	{
		position.x += glm::cos(glm::radians(rotation.y)) * .2f;
		position.z += glm::sin(glm::radians(rotation.y)) * .2f;
	}

	if (Keyboard::IsPressed(GLFW_KEY_SPACE))
	{
		position.y += .2f;
	}

	if (Keyboard::IsPressed(GLFW_KEY_LEFT_SHIFT))
	{
		position.y -= .2f;
	}

	static auto lastMousePosition = Mouse::GetPosition(window);

	if (window->HasFocus())
	{
		auto deltaPos = Mouse::GetPosition(window) - lastMousePosition;

		rotation.y += deltaPos.x * 0.05f;
		rotation.x += deltaPos.y * 0.05f;

		if (rotation.x > 90.f) rotation.x = 90.f;
		else if (rotation.x < -90.f) rotation.x = -90.f;

		if (rotation.y > 360) rotation.y = 0;
		else if (rotation.y < 0) rotation.y = 360;

		//std::cout << "Rotation: " << glm::to_string(rotation) << ", deltaPos: " << glm::to_string(deltaPos) << std::endl;

		auto cx = static_cast<int>(window->GetSize().x / 2);
		auto cy = static_cast<int>(window->GetSize().y / 2);

		Mouse::SetPosition({ cx, cy }, window);

		lastMousePosition = Mouse::GetPosition(window);
	}

	m_viewMatrix = glm::mat4(1.f);

	m_viewMatrix = glm::rotate(m_viewMatrix, glm::radians(rotation.x), { 1, 0, 0 });
	m_viewMatrix = glm::rotate(m_viewMatrix, glm::radians(rotation.y), { 0, 1, 0 });
	m_viewMatrix = glm::rotate(m_viewMatrix, glm::radians(rotation.z), { 0, 0, 1 });

	m_viewMatrix = glm::translate(m_viewMatrix, -position);

	m_projViewMatrix = m_projectionMatrix * m_viewMatrix;
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
