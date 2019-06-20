#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Player.h"
#include "../../Input/Keyboard.h"
#include "../../Input/Mouse.h"

Player::Player()
{
}

void Player::handleInput(GameWindow& window)
{
	if (Keyboard::isPressed(GLFW_KEY_W))
	{
		float speed = .2f;
		if (Keyboard::isPressed(GLFW_KEY_LEFT_CONTROL))
		{
			speed *= 3;
		}
		mAcceleration.x += -glm::cos(glm::radians(rotation.y + 90)) * speed;
		mAcceleration.z += -glm::sin(glm::radians(rotation.y + 90)) * speed;
	}

	if (Keyboard::isPressed(GLFW_KEY_S))
	{
		mAcceleration.x += glm::cos(glm::radians(rotation.y + 90)) * .2f;
		mAcceleration.z += glm::sin(glm::radians(rotation.y + 90)) * .2f;
	}

	if (Keyboard::isPressed(GLFW_KEY_A))
	{
		mAcceleration.x += -glm::cos(glm::radians(rotation.y)) * .2f;
		mAcceleration.z += -glm::sin(glm::radians(rotation.y)) * .2f;
	}

	if (Keyboard::isPressed(GLFW_KEY_D))
	{
		mAcceleration.x += glm::cos(glm::radians(rotation.y)) * .2f;
		mAcceleration.z += glm::sin(glm::radians(rotation.y)) * .2f;
	}

	if (Keyboard::isPressed(GLFW_KEY_SPACE))
	{
		mAcceleration.y += .2f;
	}

	if (Keyboard::isPressed(GLFW_KEY_LEFT_SHIFT))
	{
		mAcceleration.y -= .2f;
	}

	static auto lastMousePosition = Mouse::getPosition(&window);

	if (window.hasFocus())
	{
		auto deltaPos = Mouse::getPosition(&window) - lastMousePosition;

		rotation.y += deltaPos.x * 0.05;
		rotation.x += deltaPos.y * 0.05;

		if (rotation.x > 90.f) rotation.x = 90.f;
		else if (rotation.x < -90.f) rotation.x = -90.f;

		if (rotation.y > 360) rotation.y = 0;
		else if (rotation.y < 0) rotation.y = 360;

		//std::cout << "Rotation: " << glm::to_string(rotation) << ", deltaPos: " << glm::to_string(deltaPos) << std::endl;

		auto cx = static_cast<int>(window.getSize().x / 2);
		auto cy = static_cast<int>(window.getSize().y / 2);

		Mouse::setPosition({ cx, cy }, &window);

		lastMousePosition = Mouse::getPosition(&window);
	}
}

void Player::update(double deltaTime, World& world)
{
	velocity += mAcceleration;
	mAcceleration = { 0, 0, 0 };

	position.x += velocity.x * deltaTime;
	position.y += velocity.y * deltaTime;
	position.z += velocity.z * deltaTime;

	velocity.x *= 0.95f;
	velocity.y *= 0.95f;
	velocity.z *= 0.95f;
}
