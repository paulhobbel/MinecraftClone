#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Player.h"
#include "../../Keyboard.h"
#include "../../Mouse.h"

Player::Player()
{
}

void Player::HandleInput(GameWindow* window)
{
	if (Keyboard::IsPressed(GLFW_KEY_W))
	{
		m_acceleration.x += -glm::cos(glm::radians(rotation.y + 90)) * .2f;
		m_acceleration.z += -glm::sin(glm::radians(rotation.y + 90)) * .2f;
	}

	if (Keyboard::IsPressed(GLFW_KEY_S))
	{
		m_acceleration.x += glm::cos(glm::radians(rotation.y + 90)) * .2f;
		m_acceleration.z += glm::sin(glm::radians(rotation.y + 90)) * .2f;
	}

	if (Keyboard::IsPressed(GLFW_KEY_A))
	{
		m_acceleration.x += -glm::cos(glm::radians(rotation.y)) * .2f;
		m_acceleration.z += -glm::sin(glm::radians(rotation.y)) * .2f;
	}

	if (Keyboard::IsPressed(GLFW_KEY_D))
	{
		m_acceleration.x += glm::cos(glm::radians(rotation.y)) * .2f;
		m_acceleration.z += glm::sin(glm::radians(rotation.y)) * .2f;
	}

	if (Keyboard::IsPressed(GLFW_KEY_SPACE))
	{
		m_acceleration.y += .2f;
	}

	if (Keyboard::IsPressed(GLFW_KEY_LEFT_SHIFT))
	{
		m_acceleration.y -= .2f;
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
}

void Player::Update(float deltaTime, World& world)
{
	velocity += m_acceleration;
	m_acceleration = { 0, 0, 0 };

	position.x += velocity.x * deltaTime;
	position.y += velocity.y * deltaTime;
	position.z += velocity.z * deltaTime;

	velocity.x *= 0.95f;
	velocity.y *= 0.95f;
	velocity.z *= 0.95f;
}
